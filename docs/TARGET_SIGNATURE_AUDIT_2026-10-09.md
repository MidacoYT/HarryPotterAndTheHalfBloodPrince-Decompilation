# Audit des signatures du binaire pour les options VC8

Audit statique effectué le 9 octobre 2026 sur l’exécutable présent localement :

- Chemin : `C:\Program Files (x86)\Electronic Arts\Harry Potter et le Prince de Sang-Mêlé\pc\hp6.exe`
- SHA-256 : `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`
- Architecture : PE32 x86
- Décodage : Capstone x86 32-bit, limites de fonctions provenant de `D:\HP\reconstruction\reference\raw\exports\functions.json`
- Périmètre : 12 549 fonctions exportées en `.text`, 754 545 instructions décodées. Le seuil `< 0x680000` est seulement une approximation de la zone du jeu, pas une frontière prouvée entre modules.

Ce document sépare les signatures observées dans la cible des options réellement prouvées par recompilation d’une source exacte. Une instruction compatible avec une option ne suffit pas à établir que cette option a été utilisée.

## Signatures vérifiées dans le code cible

### SSE, SSE2 et x87

- 1 187 fonctions décodées mélangent instructions x87 et SSE scalaire.
- 29 fonctions combinent un chargement x87 `fld qword ptr [...]` et des instructions SSE scalaires.
- Une seule fonction de cet export contient les instructions de double scalaire SSE2 recherchées (`addsd`, `mulsd`, conversions correspondantes, etc.). Cela confirme que le double SSE2 est rare dans ce périmètre, pas qu’il est absent de tout le binaire.
- `0x005C0120` (180 octets) montre `fild`, `fmul`, `fdiv`, puis `fst dword ptr [esp]`, et continue en SSE avec `mulss`, `addss`, `subss` et `comiss`. C’est un bon exemple de mélange x87/SSE et d’arrondi via mémoire, mais pas une preuve de `/arch:SSE` ou `/fp:precise` sans source exacte.
- `0x00402A70` (87 octets) contient `fld qword ptr [0x848400]` et des opérations SSE. Il contient aussi un appel, donc ne satisfait pas le critère strict d’une fonction sans appel.
- `0x005496E0` (214 octets) contient `fld qword`, `divss`, des comparaisons SSE et deux appels. Il distingue la présence de ces idiomes dans la cible, mais pas `/fp` à lui seul.

Une candidate reconstruite pour `0x00404BE0` a été compilée sous plusieurs `/arch` et `/fp`, mais aucune variante n’a égalé la cible (261 octets). Ce test confirme que les options changent le code produit dans ce cas, mais son échec ne permet pas de conclure sur les flags originaux. Résultats complets : `docs/FLAG_PROBE_2026-10-09.md` et `tmp/float_matrix_404be0/`.

Un candidat bien plus discriminant existe à `0x0068EC10` : sa source reconstruite échange une globale `float` avec un argument et retourne l’ancienne valeur en `double`. Après résolution des deux relocations vers `0x8510B4`, les 25 octets correspondent avec `/O2`, `/arch:IA32` et `/fp:precise`. Les mêmes octets ne correspondent pas avec `/arch:SSE`, `/arch:SSE2`, `/fp:fast` ou `/fp:strict`. `/O2` et `/Ox` produisent tous deux la cible. C’est une preuve expérimentale forte du chemin de génération x87/précis pour cette fonction, mais pas une preuve d’un flag global : le candidat est dérivé du pseudocode IDA et n’a pas de validation sémantique indépendante.

Un deuxième candidat exact, `0x00633050`, contient un tableau local de 12 octets passé à un helper. `/O2 /GS-` produit les 21 octets cible après résolution du `REL32`; `/O2 /GS` produit 46 octets avec le cookie. Cela soutient `/GS-` ou une suppression locale pour cette compilation. À `0x00414170`, le candidat `memcpy(this+0x90, source, 0xC0)` reproduit les 24 octets cible sous `/O2`, qui termine par `rep movsd`; `/O2 /Oi-` produit un appel de 28 octets. Une pragma intrinsèque explicite permet aussi de reproduire la cible avec `/Oi-`, donc on sait que l’intrinsèque est présent, sans pouvoir distinguer l’option globale d’une pragma locale.

Un autre cas exact, `0x0043C2B0`, est un constructeur qui appelle `memset` avec une taille constante de `0x2C`. La cible conserve un appel vers le thunk à `0x6B97BC`; la reconstruction de 36 octets matche après résolution de relocation sous `/O2` **et** `/O2 /Oi-`. Cela montre qu’un appel conservé dans la cible n’implique pas `/Oi-`; la décision d’expansion dépend de la taille et du contexte.

Le test discriminant pour `/Oi` est `0x006C2030`. Une méthode C++ reconstruite fait `memcpy(this + 0x6C, src, 16)` et retourne le pointeur. Sous VC8 SP1 `/Od /RTC1`, 51 octets correspondent à la cible après résolution des deux relocations `REL32` vers `memcpy` et `__RTC_CheckEsp`; `/Od /RTC1 /Oi-` donne la même correspondance. `/Od /RTC1 /Oi` transforme la copie en code inline de 69 octets, qui ne correspond pas. C’est un indice fort que `/Oi` était désactivé ou explicitement supprimé pour cette unité. Le motif de sentinelle `0xCCCCCCCC` et l’appel RTC indiquent cependant une unité runtime-checkée distincte; ce résultat ne se généralise pas aux unités jeu optimisées.

Le même corps exact est reproduit avec `/Od /RTCs`, `/Od /RTCsu`, `/Od /RTC1` et `/Od /GZ` (en gardant `/Oi-`). `/Od /RTCu` et `/Od /RTCc` seuls divergent et n’émettent pas le même remplissage/contrôle ESP. La cible établit donc le comportement combiné de vérification des variables de pile et de l’équilibre ESP dans cette fonction, mais pas le switch exact parmi les alias/supersets.

### Instructions REP et fonctions intrinsèques

Le décodage complet compte les instructions suivantes. Les colonnes séparent le code sous `0x680000` (approximation du code de jeu) du reste de `.text` :

| Idiome | Zone jeu approximative | Reste de `.text` | Total |
|---|---:|---:|---:|
| `rep movsd` | 109 | 62 | 171 |
| `rep stosd` | 29 | 100 | 129 |
| `repe cmpsb` | 127 | 10 | 137 |
| `rep movsb` | 6 | 28 | 34 |
| `repe cmpsd` | 0 | 13 | 13 |
| `rep stosb` | 0 | 9 | 9 |
| `rep movsw` | 0 | 1 | 1 |
| `rep stosw` | 0 | 1 | 1 |
| `repz ret` | 0 | 1 | 1 |

Les nombres sont des instructions décodées, pas nécessairement des appels à `memcpy`/`memset` générés par `/Oi`. Un `rep` peut provenir d’un assembleur, d’une bibliothèque ou d’une autre transformation. Ils ne démontrent donc pas `/Oi` sans vérifier une fonction exacte et son origine.

### Convention d’appel en registres et LTCG

Des exports d’instructions précédents montrent quatre paires appelant–appelé où l’appelant place une valeur dans `EAX` et l’appelé la consomme dès son entrée : `0x45F380→0x45F3B0`, `0x4A24D0→0x4A2500`, `0x4082F0→0x408320`, `0x45DF50→0x45DF80`. C’est une convention interne en registre, distincte du `__fastcall` MSVC usuel. Cette observation ne prouve pas `/GL`: assembleur ou convention personnalisée restent possibles. Le corpus d’instructions qui a fourni ces paires est limité à 390 fonctions.

Un probe de `0x0057B500` produit le même corps exact sous compilation ordinaire et sous `/GL` + `/LTCG`; il ne départage donc pas les hypothèses. Voir `docs/LTCG_PROBE_2026-10-09.md`.

### `/GS`

Dans `functions_hp6.csv`, les 30 fonctions marquées comme utilisant le cookie GS sont toutes à partir de `0x6B9B9C`. Il n’y en a aucune parmi les 4 198 fonctions normales sous `0x680000`. C’est cohérent avec `/GS-` dans le code de jeu détecté, mais les limites de fonctions sont heuristiques et l’absence d’un appel au contrôle cookie n’exclut pas toute protection GS.

## Révision CRT : résultat du test direct

Le code cible de `__security_init_cookie` à `0x6B9E41` correspond au membre VC8 RTM `gs_support.obj` après prise en compte de ses 9 relocations `IMAGE_REL_I386_DIR32`; les octets non-relocatifs sont identiques. La même routine existe donc déjà en RTM. Ce test ne distingue pas RTM `.42` de SP1 `.762`.

Le membre RTM `rtm_crtexe.obj` trouvé localement porte `___tmainCRTStartup` sur 374 octets, tandis que la fonction ciblée à `0x6B9457` est classée sur 479 octets par l’export IDA. Cette comparaison ne tranche pas : frontières, variante de démarrage et version CRT peuvent différer. L’entrée à `0x6B9718` est un stub de 10 octets qui appelle `__security_init_cookie` puis saute vers `__tmainCRTStartup` à `0x6B9457`.

La bibliothèque CRT VC8 SP1 n’a pas encore été trouvée localement. Tant que le membre SP1 correspondant n’est pas comparé au même endroit, la révision RTM/SP1 reste indéterminée.

## Bilan de preuve

| Propriété | État après cet audit |
|---|---|
| VC8 32-bit, famille 14.00.50727 | Fortement soutenu par les analyses précédentes du PE et du Rich Header |
| SP1 `.762` plutôt que RTM `.42` | Pas tranché par les probes de code ordinaires; le test CRT cookie est identique en RTM |
| `/O2` ou `/Ox` plutôt que `/O1`/`/Os` | Favorisé par les matrices de fonctions reconstruites exactes, sans départager `/O2` de `/Ox` |
| `/Oy` | Variable selon les fonctions; plusieurs fonctions perdent le match avec `/Oy-`, d’autres restent identiques |
| `/arch` et `/fp` pour `0x0068EC10` | Fortement discriminés par compilation exacte : chemin IA32/x87 et `/fp:precise` correspondent; SSE/SSE2 et fast/strict divergent |
| `/Oi` à `0x00414170` et `0x006C2030` | Le premier montre l’expansion sous `/O2`; le second distingue réellement `/Od /RTC1 /Oi-` de `/Oi` pour une unité runtime-checkée |
| `/GS-` à `0x00633050` | `/GS-` correspond et `/GS` diverge pour la candidate locale à tableau de 12 octets |
| `/Ob`, `/GL` globaux | Toujours non prouvés par un test exact discriminant |
| `/GS-` global dans la zone de jeu | Les indices statiques et le candidat discriminant concordent, mais ne prouvent pas que chaque unité utilise le même réglage |

## Reproduction

Le scanner local temporaire est `tmp/audit_target_signatures.py`; son résultat brut est `tmp/target_signature_audit_20261009.json`. Il lit le binaire local ci-dessus et les exports IDA. Les tests de compilation et extractions CRT sont conservés dans les répertoires `tmp/` indiqués dans les deux rapports liés. Aucun fichier du jeu n’a été copié dans le dépôt.
