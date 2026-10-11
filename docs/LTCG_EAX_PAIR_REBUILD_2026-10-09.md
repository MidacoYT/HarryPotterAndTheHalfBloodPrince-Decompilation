# Reproduction de l’ABI EAX avec VC8 SP1 `/GL`

## Test

J’ai compilé deux petits TUs C++ avec le VC8 SP1 local (`14.00.50727.762`), en `/O2 /GS- /Gy`, puis lié une DLL `/NOENTRY /NODEFAULTLIB`. Le helper, marqué `__declspec(noinline)`, reçoit un pointeur et initialise les champs à partir de ce pointeur. Le wrapper prend le pointeur sur la pile, appelle le helper, puis écrit à l’offset `0x50`.

En compilation ordinaire, le wrapper émet `push esi; call helper`; le helper récupère son pointeur dans `[esp+4]`. En compilant les mêmes deux TUs avec `/GL` et liant avec `/LTCG`, le wrapper charge `eax` avec l’argument et appelle sans empiler l’argument. Le helper commence alors par `and byte ptr [eax+7Ch],80h`, puis utilise EAX comme base pour ses accès mémoire.

Extraits désassemblés des DLL du test :

```asm
; sans /GL, wrapper
push esi
mov  esi, [esp+8]
test esi, esi
je   ...
push esi
call helper

; /GL + /LTCG, wrapper
mov  eax, [esp+4]
test eax, eax
je   ...
call helper

; helper LTCG
and  byte ptr [eax+7Ch], 80h
```

Les sources, objets, DLLs et le script de désassemblage sont dans `tmp/ltcg_pair_rebuild/`.

## Correspondance avec les quatre paires du jeu

J’ai extrait les corps complets de `hp6.exe` (SHA-256 `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`) avec les frontières IDA locales. Les quatre appelants font 39 octets chacun; les callees font respectivement 243, 154, 190 et 376 octets. Chaque appelant charge EAX depuis ESI avant l’appel, et chaque callee commence par `and byte ptr [eax+7Ch],80h`.

Le même motif apparaît pour chacune :

| Appelant → appelé | Chargement avant l’appel | Première instruction du callee |
|---|---|---|
| `0x45F380 → 0x45F3B0` | `mov eax, esi` à `0x45F387`; appel à `0x45F38B` | `and byte ptr [eax+7Ch],80h` |
| `0x4A24D0 → 0x4A2500` | `mov eax, esi` à `0x4A24D7`; appel à `0x4A24DB` | même instruction |
| `0x4082F0 → 0x408320` | `mov eax, esi` à `0x4082F7`; appel à `0x4082FB` | même instruction |
| `0x45DF50 → 0x45DF80` | `mov eax, esi` à `0x45DF57`; appel à `0x45DF5B` | même instruction |

Les candidats C exportés pour les quatre appelants ne compilent pas encore : appels aux helpers non déclarés et expression Hex-Rays `MEMORY` invalide en C. Pour `0x45F380 → 0x45F3B0`, j’ai corrigé ces problèmes dans un petit couple de source reconstruit et recompilé les deux TUs.

Cette source reste incomplète : le caller LTCG fait 21 octets contre 39 dans la cible; le caller ordinaire fait 30 octets; le callee reconstruit fait 139 octets contre 243 dans la cible. Aucun corps entier ne correspond exactement, ni en compilation ordinaire ni en LTCG. Les différences reflètent surtout le pseudo-source incomplet et les champs manquants dans le callee, et ne permettent pas de juger le flag depuis l’échec de matching.

## Conclusion et prochain test

Le motif EAX n’est pas le `__fastcall` MSVC usuel (ECX/EDX). Le test contrôlé montre que VC8 SP1 LTCG peut créer cette convention interne à partir d’un helper non exporté et non inliné; l’absence d’argument sur la pile dans les callsites du jeu est ainsi compatible avec `/GL` sur leurs TUs. Les quatre corps complets du jeu sont maintenant confirmés comme utilisant ce motif.

Pour attribuer `/GL` à ces adresses avec preuve binaire, reconstruire un couple caller/callee complet avec déclarations C++ et globals/vtables corrects, le compiler avec/sans `/GL`, puis comparer tous les octets et relocations au binaire original. Les artefacts du test et l’extracteur des corps cible sont dans `tmp/ltcg_pair_rebuild/`.
