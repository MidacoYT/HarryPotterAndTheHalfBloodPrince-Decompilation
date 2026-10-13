# Harry Potter and the Half-Blood Prince — Decompilation

An unofficial, function-by-function decompilation project for the **Windows PC** release of Harry Potter and the Half-Blood Prince (2009).

## Current progress

- Target executable: `hp6.exe`, version `1.0.0.1`, SHA-256 `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`.
- The current objdiff report covers all 10,992 inventoried functions. 2,422 functions match exactly (22.03% by function count).
- Exact machine-code coverage is 30,302 of 2,530,025 code bytes (1.20%).
- Recompiling 83 existing nonmatching C candidates with VC8 SP1 `/O2` produced 21 exact matches. Fixing C89 declaration order made five more sources compile; `fn_006F2514` now matches 30/30 bytes. Rewriting `fn_0057BA10` without an intermediate also matches 34/34 bytes. The latest report was generated from the rebuilt objects.
- This pass added 178 C matching candidates, each rebuilt and byte-checked with VC8 SP1; 108 use per-function compiler switches recorded in the manifest. Recent batches found 68 matches through compiler-option sweeps, 9 after allowing undeclared internal calls, 1 after adding a typed global declaration at its recorded address, and 5 with alternate optimizer flags. Their options and relocations are recorded in the manifest. Source semantics remain inferred from the binary and are not independently validated.
- Added a custom Capstone-based decompiler (`tools/own_decompiler.py`) that transliterates supported x86 control flow into C without guessing, plus an LTCG-based matcher for register-passed arguments. Its experimental matcher and batch scripts remain under `tmp/autodecomp/`. The decompiler validates CFG branch targets and propagates register, flags, and stack-frame state before lowering. The original matcher pass recorded 19 new exact matches.
- The `own_batch_test.py` flow uses `tools/own_decompiler.py` as its only source of reconstructed function bodies, signatures, and call arguments. Its separate support modules only compile and compare candidates with VC8.

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
$env:HP6_CL = 'C:\Path\To\VC8-SP1\cl.exe'
python tools/build.py build/fn_00401030.obj
.\tools\get-objdiff.ps1
.\tools\objdiff-cli.exe report generate -p . -o report.json -f json
```

This requires Python and an x86 MSVC compiler. To reproduce the current exact matches, set `HP6_CL` to a compatible VC8 SP1 compiler; a newer MSVC can produce different code. `extract_target.py` verifies the executable fingerprint and writes private target objects under `expected/`. `build/`, `expected/`, and the downloaded objdiff executable are ignored by Git. The tracked `report.json` contains matching measures only.

## decomp.dev

The GitHub Actions workflow uploads the committed version-2 `report.json` as the `pc_report` artifact. After changing reconstructed C, regenerate `report.json` locally and commit it with the source changes. The hosted workflow only validates and uploads this report; the game executable and target objects never leave your PC.

## Scope

This repository contains reconstructed source, build metadata, and objdiff measures only. It does not include the original executable, game archives, extracted assets, or generated target objects. Background information may be consulted from `D:\HP` documentation; no code or build artifacts are copied from that directory.

Unofficial fan research project; not affiliated with or endorsed by Electronic Arts, Warner Bros., or the original developers. All Harry Potter intellectual property remains with its respective owners.
