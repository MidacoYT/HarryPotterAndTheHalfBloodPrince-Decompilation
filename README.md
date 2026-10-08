# Harry Potter and the Half-Blood Prince — Decompilation

An unofficial, function-by-function decompilation project for the **Windows PC** release of Harry Potter and the Half-Blood Prince (2009).

## Current progress

- Target executable: `hp6.exe`, version `1.0.0.1`, SHA-256 `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`.
- `fn_405090`: reconstructed from its seven x86 instructions and exact under local objdiff.
- `fn_48AE70` (documented as `DeactivateScreenNoFocus`): high-level C control flow reconstructed; currently a 74.17% fuzzy objdiff match with the installed MSVC toolset.
- Current report: 2 functions, 1 byte-exact, 45 total code bytes, 78.19% aggregate fuzzy similarity. This is an initial slice, not whole-game coverage.

Symbols remain address-based for reliable objdiff matching; confirmed function roles are recorded in source comments and [the setup and evidence notes](docs/DECOMPILATION_SETUP.md).

## Local workflow

The game executable and generated target objects are not tracked. Use the copy from your own installation:

```powershell
$env:HP6_EXE_PATH = 'C:\Program Files (x86)\Electronic Arts\Harry Potter et le Prince de Sang-Mêlé™\pc\hp6.exe'
python tools/extract_target.py --exe $env:HP6_EXE_PATH
python tools/build.py build/fn_405090.obj
python tools/build.py build/fn_48AE70.obj
.\tools\get-objdiff.ps1
.\tools\objdiff-cli.exe report generate -p . -o build/report.json -f json-pretty
```

This requires Python and the Visual Studio x86 C compiler. `extract_target.py` verifies the executable fingerprint and writes private target objects under `expected/`. `build/`, `expected/`, and the downloaded objdiff executable are ignored by Git.

## decomp.dev report workflow

`.github/workflows/report.yml` builds a report on a self-hosted Windows runner so the original executable never leaves the runner. Configure a GitHub Actions runner with the `hp6-decomp` label and set the repository variable `HP6_EXE_PATH` to that runner's local `hp6.exe` path. The workflow uploads only the objdiff JSON report as `pc_report`.

## Scope

This repository contains reconstructed source and build metadata only. It does not include the original executable, game archives, extracted assets, or generated target objects. Background information may be consulted from `D:\HP` documentation; no code or build artifacts are copied from that directory.

Unofficial fan research project; not affiliated with or endorsed by Electronic Arts, Warner Bros., or the original developers. All Harry Potter intellectual property remains with its respective owners.
