# Harry Potter and the Half-Blood Prince — Decompilation

An unofficial, function-by-function decompilation project for the **Windows PC** release of Harry Potter and the Half-Blood Prince (2009).

## Current progress

- Target executable: `hp6.exe`, version `1.0.0.1`, SHA-256 `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`.
- `fn_405090`: reconstructed from its seven x86 instructions and exact under local objdiff.
- `fn_48AE70` (documented as `DeactivateScreenNoFocus`): reconstructed in C; currently an 82.22% fuzzy objdiff match with MSVC 19.52.
- The committed report covers 2 functions and 45 code bytes: 1 exact function and 84.99% aggregate fuzzy similarity. This is an initial slice, not whole-game coverage.

Symbols remain address-based for reliable objdiff matching; confirmed function roles are recorded in source comments and [the setup and evidence notes](docs/DECOMPILATION_SETUP.md).

## Local workflow

The game executable and generated target objects stay on your PC. Use the copy from your own installation:

```powershell
$env:HP6_EXE_PATH = 'C:\Program Files (x86)\Electronic Arts\Harry Potter et le Prince de Sang-Mêlé™\pc\hp6.exe'
python tools/extract_target.py --exe $env:HP6_EXE_PATH
python tools/build.py build/fn_405090.obj
python tools/build.py build/fn_48AE70.obj
.\tools\get-objdiff.ps1
.\tools\objdiff-cli.exe report generate -p . -o report.json -f json
```

This requires Python and the Visual Studio x86 C compiler. `extract_target.py` verifies the executable fingerprint and writes private target objects under `expected/`. `build/`, `expected/`, and the downloaded objdiff executable are ignored by Git. The tracked `report.json` contains matching measures only.

## decomp.dev

The GitHub Actions workflow uploads the committed version-2 `report.json` as the `pc_report` artifact. After changing reconstructed C, regenerate `report.json` locally and commit it with the source changes. The hosted workflow only validates and uploads this report; the game executable and target objects never leave your PC.

## Scope

This repository contains reconstructed source, build metadata, and objdiff measures only. It does not include the original executable, game archives, extracted assets, or generated target objects. Background information may be consulted from `D:\HP` documentation; no code or build artifacts are copied from that directory.

Unofficial fan research project; not affiliated with or endorsed by Electronic Arts, Warner Bros., or the original developers. All Harry Potter intellectual property remains with its respective owners.
