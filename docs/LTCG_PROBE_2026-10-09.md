# VC8 LTCG probe - 2026-10-09

## Controlled check

The local VC8 SP1 compiler is `14.00.50727.762`. Compiling a two-translation-unit C++ probe with `/GL` produced anonymous COFF objects (about 4.2 KB each, without ordinary machine-code function sections). Linking them with VC8 SP1 `link.exe` and `/LTCG` printed `Generating code` / `Finished generating code`. Linking without an explicit `/LTCG` also succeeded: the linker detected `/GL` objects, restarted itself in LTCG mode, and advised that adding `/LTCG` would improve performance. Thus `/GL` input is sufficient for the linker to activate LTCG; the PE cannot reveal whether `/LTCG` was written explicitly on the original command line.

## Target candidate test

Candidate source for `0x0057B500` was compiled both as ordinary x86 C under `/O2 /GS- /Gy` and as an LTCG input under `/GL /O2 /GS-`; the latter was linked into a small DLL with LTCG and its exported function body extracted. Both paths produced the same 61 bytes, which match the saved target reference for that address exactly.

This proves VC8 SP1 can generate this candidate body through either ordinary compilation or LTCG. It does not identify which path produced the game's function. The ordinary and LTCG outputs are byte-identical, and the candidate source itself is reconstructed rather than confirmed as the original source.

## Relation to the target Rich header

The executable's 27 `Utc1400_LTCG_CPP` Rich records support the presence of LTCG-generated C++ inputs among the link inputs. Available IDA exports and `functions_hp6.csv` do not map those records or their source objects to final function addresses. The experiment therefore cannot label any individual function as LTCG-generated, measure surviving LTCG code, or recover `/GL`/`/LTCG` settings per translation unit.

To make that attribution, the missing evidence would be original object files, PDB/ILTCG provenance, or a linker map/object-to-address record. A match of final bytes alone is insufficient when the ordinary and LTCG pipelines produce the same bytes.

## Artifacts

The probe source, objects, linked DLLs, and byte extractor are retained under ignored `tmp/ltcg_probe/`. No game files or original executable were copied into the repository.

## Actual target register-ABI pairs and controlled LTCG comparison

A targeted extraction of the original PE confirmed the four EAX pairs previously found in instruction exports. The callers load an object/context pointer into `EAX` just before the call; each callee starts by consuming it as `[eax+0x7C]` (for example, `0x45F380 -> 0x45F3B0`). The complete target bodies are now verified from the executable, not only from the smaller instruction export.

I also compiled a two-translation-unit C++ control. Without LTCG, the caller pushes the argument and the helper reads `[esp+4]`. With VC8 SP1 `/GL` + `/LTCG`, the caller loads the argument into `EAX` and the helper consumes it from `EAX`, matching the target's register-ABI shape. This establishes that LTCG can explain the observed convention.

It does not attribute those specific game functions to LTCG: the available reconstructed caller/callee sources do not match the complete target bodies (target caller/callee are 39/243 bytes for the inspected pair; reconstructed LTCG bodies are 21/135 bytes). A custom calling convention, hand-written assembly, or other per-object mechanism remains possible. Exact object-to-address provenance is still missing. Extraction and controls are under `tmp/ltcg_pair_rebuild/`.
