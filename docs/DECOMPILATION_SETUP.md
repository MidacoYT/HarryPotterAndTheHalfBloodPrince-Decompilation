# Decompilation setup and evidence

## Target

- Edition: Windows PC, Harry Potter and the Half-Blood Prince.
- Executable: the user's installed `hp6.exe`.
- File version: `1.0.0.1`.
- SHA-256: `41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10`.
- PE: 32-bit x86, image base `0x400000`, linker version `8.00`.

The executable and game data stay in the user's installation. Generated expected object files are local and Git-ignored. The PE reports linker version 8.00. The `D:\HP` notes list MSVC 14.00.50727.762 (Visual C++ 2005 SP1) as a candidate compiler. Current MSVC 19.52 generates a different entry sequence, so no exact C match is claimed.

The documentation in `D:\HP` identifies this same executable fingerprint and records the VC2005 SP1 x86 compiler candidate. It reports earlier function-level matching experiments, but also states that a complete executable rebuild has not been achieved. These notes are background only; no code, binaries, or build artifacts from `D:\HP` are part of this repository.

## Reconstructed functions

### `fn_405090`

At `0x405090`, the target instructions are `mov dword ptr [ecx], 0x8202B8; ret`. The current C translation stores the same 32-bit constant through its sole fastcall argument. Its seven emitted bytes match the locally extracted target bytes exactly under objdiff 3.8.2. The symbol remains address-based because its original name and higher-level meaning have not been established.

### `fn_48AE70`

At `0x48AE70`, the reference notes in `D:\HP` identify the routine as `DeactivateScreenNoFocus`. Its code reads the manager pointer at `0x00FCADE8`, passes the input through the lookup at `0x53CC00`, and, when an entry is found, calls `0x53CF50` before returning 1; otherwise it returns 0. The source is a high-level C reconstruction of this observed control flow. Its current MSVC 19.52 build has an 82.22% fuzzy objdiff match and is not exact. The remaining mismatch is concentrated in the compiler-generated entry sequence and register allocation.

## Local target object generation

`tools/extract_target.py` verifies the executable SHA-256, maps function virtual addresses through the PE `.text` section, and creates local x86 COFF target objects. The 38-byte `fn_48AE70` object records its two observed relative-call relocations. This object packaging is a comparison input generated from the user's executable, not an original compiler-produced object; it remains under ignored `expected/` and is never uploaded.

## objdiff and decomp.dev

objdiff supports x86 and compares relocatable object files. `objdiff.json` pairs each local target object with the corresponding object compiled from reconstructed source. Generate the tracked report locally with:

```powershell
.\tools\objdiff-cli.exe report generate -p . -o report.json -f json
```

The version-2 report contains function sizes and matching measures only. The GitHub Actions workflow uploads it as the `pc_report` artifact that decomp.dev reads. After source changes, regenerate and commit `report.json` with the source changes. GitHub's hosted runner does not need the game executable or a self-hosted runner.

The current report covers two functions and 45 code bytes: one exact function and 84.99% aggregate fuzzy similarity. It is an early progress snapshot, not whole-game coverage.

No full executable rebuild is claimed.
