# Decompilation setup

The current toolchain evidence, experimental commands/results, pinned executable fingerprint, and remaining unknowns are documented in [TOOLCHAIN_ANALYSIS.md](TOOLCHAIN_ANALYSIS.md).

## Local tools

- Windows x86 MSVC is available through `tools/build.py`; set `HP6_CL` to choose a specific compiler.
- objdiff-cli 3.8.2 is kept in `tools/objdiff-cli.exe`.
- `tools/audit_pe.py` audits PE32 headers, sections, imports, exports, relocation/debug directories, and selected runtime markers using Python's standard library.
- `tools/extract_target.py` verifies the expected game SHA-256 before extracting target function bytes into local COFF comparison objects.

The executable and expected objects stay local. Generated COFF objects under `expected/` are comparison inputs, not original linker outputs. The repository does not contain the game executable, the VC2005 compiler, or the SDK ISO.

Build one listed candidate object with:

```powershell
python tools/build.py build/fn_004DA3D0.obj
```

To regenerate local expected COFF objects, use `tools/extract_target.py --exe <installed hp6.exe>`. It rejects any executable whose SHA-256 differs from the fingerprint in the script. Compare objects with:

```powershell
.\tools\objdiff-cli.exe diff -1 expected\fn_004DA3D0.obj -2 build\fn_004DA3D0.obj --format json
```

An exact function-body match does not establish matching whole-object metadata, linker output, executable sections, or the original toolchain. No whole-executable rebuild is currently claimed.
