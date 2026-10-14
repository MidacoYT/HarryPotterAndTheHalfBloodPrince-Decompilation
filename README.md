# Harry Potter and the Half-Blood Prince — Decompilation

An unofficial, function-by-function decompilation project for the **Windows PC** release of Harry Potter and the Half-Blood Prince (2009).

## Current progress

- Target executable: `hp6.exe`, version `1.0.0.1`, SHA-256 `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`.
- The current report covers all 10,992 inventoried functions. 4,689 functions match exactly (42.66% by function count).
- Exact machine-code coverage is 1,172,768 of 2,533,903 code bytes (46.28%).
- All 492 functions larger than 1,024 bytes now match through verified, readable MASM instruction reconstruction. These assembly sources preserve the executable's code; they do not recover the original C or C++ source. Six function extents were extended to their decoded return before matching.
- [C pseudocode candidates for all 492 large functions](research/large_c/README.md) are now available for reading and further reconstruction. Hex-Rays exported 484, and the in-project translator supplied 8 fallbacks. None has been promoted as an exact C build source; the ASM match and report remain unchanged.
- A 3,000-function triage of the smallest remaining unmatched units produced 327 new exact matches: 278 ordinary VC8 recompilations, 24 LTCG builds, 23 reassembled indirect dispatchers, and 2 control-flow restructurings. Every new unit was rebuilt through the project builder and checked against its normalized target object, including call relocations. The report was updated from those verified objects and the previous full objdiff report; the other units retain their previous measures.
- A full re-triage of all 6,308 still-unmatched functions added 5 more exact matches (4,684 → 4,689). The remaining unmatched mass is structurally resistant to statement-level C reconstruction: most units are mid-function fragments/shared tails rather than real entry points, alignment padding that C cannot express, or cases where VC8 `/O2` reoptimizes reconstructed statements into different code than the original richer source. See [MODLOG.md](MODLOG.md) for the per-pool measurements.
- Recompiling 83 existing nonmatching C candidates with VC8 SP1 `/O2` produced 21 exact matches. Fixing C89 declaration order made five more sources compile; `fn_006F2514` now matches 30/30 bytes. Rewriting `fn_0057BA10` without an intermediate also matches 34/34 bytes. The latest report was generated from the rebuilt objects.
- This pass added 178 C matching candidates, each rebuilt and byte-checked with VC8 SP1; 108 use per-function compiler switches recorded in the manifest. Recent batches found 68 matches through compiler-option sweeps, 9 after allowing undeclared internal calls, 1 after adding a typed global declaration at its recorded address, and 5 with alternate optimizer flags. Their options and relocations are recorded in the manifest. Source semantics remain inferred from the binary and are not independently validated.
- The Capstone-based decompiler (`tools/own_decompiler.py`) translates supported x86 control flow into C. The matcher and its support modules are in `tools/`. Temporary candidate files and compiler probes are generated locally and can be removed without changing reconstructed sources or the committed report.

## Run the own decompiler directly

Pass only the executable path to scan its executable sections, decompile detected function candidates, and verify byte matches:

```powershell
python .\tools\own_decompiler.py "D:\Games\Harry Potter and the Half-Blood Prince\pc\hp6.exe"
```

It writes generated C files and a live `report.json` under `build/own_decompiled/`. The report is refreshed every 25 candidates and on each skip/error; `errors.jsonl` is flushed immediately for each unsupported function, matching error, or compiled byte difference. Discovery uses executable bytes only; it does not read the function CSV or manifest. Candidate discovery and sizes are heuristic, so the report distinguishes detected candidates from verified exact matches. To try one address, pass it with `--size 0xNN`; add `-o .\function.c` to save that C output.

Symbols remain address-based for reliable objdiff matching; confirmed function roles are recorded in source comments and [the setup and evidence notes](docs/DECOMPILATION_SETUP.md).

## Local workflow

The game executable and generated target objects stay on your PC. Use the copy from your own installation:

```powershell
$env:HP6_EXE_PATH = 'C:\Program Files (x86)\Electronic Arts\Harry Potter et le Prince de Sang-Mêlé™\pc\hp6.exe'
python tools/extract_target.py --exe $env:HP6_EXE_PATH
python tools/make_unmatched_stubs.py
$env:HP6_CL_VC8 = 'C:\Path\To\VC8-SP1\cl.exe'
python tools/build.py build/fn_00401030.obj
python tools/audit_clean_rebuild.py
.\tools\get-objdiff.ps1
.\tools\objdiff-cli.exe report generate -p . -o report.json -f json
```

This requires Python and an x86 MSVC compiler. To reproduce the current exact matches, set `HP6_CL_VC8` to a compatible VC8 SP1 compiler; a newer MSVC can produce different code. `extract_target.py` verifies the executable fingerprint and writes private target objects under `expected/`. `build/`, `expected/`, and the downloaded objdiff executable are ignored by Git. The tracked `report.json` contains matching measures only.

Run `clean-temp.bat` from the repository root to remove generated `tmp/`, `build/`, and `expected/` directories, Python caches, and root-level probe files. The executable and reconstructed sources are untouched. Regenerate target objects and compiled candidates with the commands above when needed.

## decomp.dev

The GitHub Actions workflow uploads the committed version-2 `report.json` as the `pc_report` artifact. After changing reconstructed C, regenerate `report.json` locally and commit it with the source changes. The hosted workflow only validates and uploads this report; the game executable and target objects never leave your PC.

## Scope

This repository contains reconstructed source, build metadata, and objdiff measures only. It does not include the original executable, game archives, extracted assets, or generated target objects. Background information may be consulted from `D:\HP` documentation; no code or build artifacts are copied from that directory.

Unofficial fan research project; not affiliated with or endorsed by Electronic Arts, Warner Bros., or the original developers. All Harry Potter intellectual property remains with its respective owners.
