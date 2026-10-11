# Comparaison des archives CRT RTM et SP1 dans `hp6.exe`

## Conclusion

Deux corps CRT de la cible correspondent aux membres de l’archive VC8 SP1 locale et divergent du membre RTM correspondant : `__onexit` et `__IsNonwritableInCurrentImage`. C’est une preuve forte que ces implémentations proviennent de l’archive CRT SP1, ou d’une compilation équivalente des mêmes sources SP1. Cela identifie la révision de cette partie du CRT lié; cela ne prouve pas que le code du jeu a été compilé par `cl.exe` SP1.

Cette analyse corrige la recherche antérieure résumée dans `TOOLCHAIN_ANALYSIS.md` (section « Local search for a servicing-matched VC8 archive ») : l’archive SP1 avait été manquée parce qu’elle se trouvait dans le cache d’extraction du SDK, sans suffixe `.lib`. Les formulations antérieures indiquant qu’aucune archive CRT SP1 n’était disponible sont donc obsolètes. Le fichier principal n’a pas été réécrit, car son encodage historique est mixte; ce rapport daté est la mise à jour de référence.

## Sources comparées

- RTM : `D:\HP\reconstruction\matching\toolchain\vc2005-rtm-admin3\Program Files\Microsoft Visual Studio 8\Vc7\lib\msvcrt.lib`; SHA-256 `B1456D9A7E17865E3DC35663E0377BE4C7B8BE97A372210CD064F9F5635DFFEA`.
- Archive CRT x86 tirée du Windows SDK de février 2007 local : `D:\HP\reconstruction\matching\runs\sdk_lib_probe\msvcrt_lib.65224FD3_6336_4D71_AEC1_EB053C788554`; SHA-256 `9D64B0C4721D2AE327B8D6C041B5A0D2EA72237FE86B5AEBD9A93E9F2EEB0049`.
- L’archive SDK est distincte de l’archive RTM et contient `gs_support.obj`, `atonexit.obj`, `pesect.obj` et `crtexe.obj`. Son environnement SDK contient également les runtimes VC80 `.762`, ce qui identifie la candidate comme le jeu de bibliothèques SP1 documenté dans `TOOLCHAIN_ANALYSIS.md`. Les extractions temporaires sont dans `tmp/crt_revision_probe/`.
- L’exécutable cible est identifié par SHA-256 `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`.

## Fonctions discriminantes

Les octets cible ont été extraits aux adresses indiquées et comparés aux sections COFF des membres des deux archives. La comparaison neutralise seulement les champs couverts par des relocations, puis compare strictement le reste du corps.

| Fonction cible | Corps cible | Membre SP1 | Membre RTM | Résultat |
|---|---:|---:|---:|---|
| `__onexit`, `0x006B92C8` | 165 octets | `atonexit.obj`, 165 octets, 0 différence non-reloc | `atonexit.obj`, 159 octets, 57 différences non-reloc | SP1 correspond; RTM exclu pour ce corps |
| `__IsNonwritableInCurrentImage`, `0x006B9D50` | 187 octets | `pesect.obj`, 187 octets, 0 différence non-reloc | `pesect.obj`, 108 octets, 79 différences non-reloc | SP1 correspond; RTM exclu pour ce corps |

Les relocations SP1 pointent vers les fonctions et données attendues dans l’image, notamment les aides SEH, le cookie, les limites de la table `onexit` et les imports du CRT. Le matching ne repose donc pas seulement sur des octets identiques dans des zones arbitraires.

## Contrôles qui ne départagent pas les révisions

- `__security_init_cookie` à `0x006B9E41` : code non-reloc identique aux objets RTM et SP1, 148 octets après prise en compte de 9 relocations.
- `___tmainCRTStartup` : la section de démarrage est 374 octets dans les deux archives et les deux corps bruts sont identiques. La fonction classée dans la cible à `0x006B9457` fait 479 octets et ne correspond directement à aucun de ces membres.
- `__ValidateImageBase` (41 octets) et `__FindPESection` (66 octets) de `pesect.obj` correspondent tous deux aux versions RTM et SP1.

Le `@comp.id` COFF observé est `0x006DC627` dans les membres RTM et `0x006EC627` dans ceux du SDK. Je le conserve comme preuve de provenance des objets, sans l’interpréter seul comme numéro de patch : les Rich records du PE identifient la famille 50727, mais n’encodent pas directement `.42` ou `.762`.

## Extension du scan des membres modifiés

J’ai aussi comparé les fonctions COFF reconnues dans les quatre membres dont le contenu diffère entre les deux archives (`atonexit.obj`, `crtdll.obj`, `error.obj`, `pesect.obj`) aux fonctions de l’inventaire PE. La comparaison exige la même longueur et l’égalité de tous les octets hors champs de relocation. Elle retrouve, dans les deux révisions, `_atexit` à `0x006B936D`, cinq fonctions de diagnostic/runtime-check de `error.obj` entre `0x006F36B8` et `0x006F3990`, ainsi que `__ValidateImageBase` et `__FindPESection` de `pesect.obj` à `0x006B9CD0` et `0x006B9D00`. Ces fonctions ne départagent donc pas RTM et SP1. Le corps SP1 de `__IsNonwritableInCurrentImage` est un match supplémentaire à `0x006B9D50`; le corps RTM est plus court et ne peut pas correspondre. Le corps SP1 de `__onexit` est confirmé séparément dans le tableau ci-dessus.

Ce scan n’est pas une preuve exhaustive pour les fonctions sans symbole ou manquées par l’inventaire heuristique. Dans les fonctions nommées des membres modifiés qui ont été attribuées par comparaison, toutefois, aucun troisième corps ne fournit une signature RTM/SP1 différente en plus de `__onexit` et `__IsNonwritableInCurrentImage`.

## Portée et suite

**Établi avec forte confiance :** au moins deux fonctions du CRT lié dans `hp6.exe` correspondent aux implémentations de l’archive SP1 et non aux membres RTM comparés. Cela tranche la révision de ces objets CRT, sous réserve qu’aucune recompilation locale de sources identiques n’ait reproduit les mêmes octets.

**Non établi :** la révision de `cl.exe` utilisée pour le code du jeu, tous les flags par module, le patch exact de `link.exe` et la révision du SDK DirectX. Les corps de code jeu compilables par RTM et SP1 restent souvent identiques; il faut traiter séparément la provenance du CRT, du compilateur de jeu et du linker.
