# VC8 flag probe - 2026-10-09

## Setup

I compiled five existing C reconstruction candidates with the local Microsoft Visual C++ 8.0 SP1 compiler (`cl.exe` 14.00.50727.762, x86). All five addresses are listed as `normal` in `functions_hp6.csv`; none is marked with a GS cookie, and each is classified `noframe`:

| Address | Target body size |
|---|---:|
| `0x0057B500` | 61 bytes |
| `0x0059CF20` | 50 bytes |
| `0x0059CF60` | 50 bytes |
| `0x005E3940` | 44 bytes |
| `0x0065FF90` | 36 bytes |

Each candidate source already produced an exact target-body match under `/O2 /GS- /Gy`. The reference byte strings and sizes were taken from the corresponding existing adapted reports under `D:\HP\reconstruction\matching\adapted\reports`. I compiled 16 flag variants per function, extracted `.text` bytes from the COFF objects, and compared them byte for byte with those references. All 80 compile attempts succeeded.

These are reconstructed C candidates. Their machine-code equality is experimentally verified, but their semantic validation as the original source is not established. Results therefore show which flags can reproduce these five bodies from these candidate sources; they do not prove the game's project-wide flags.

## Results

| Variant | Exact bodies |
|---|---:|
| Baseline `/O2 /GS- /Gy` | 5/5 |
| Suggested `/O2 /Ot /Oi /Oy /GS- /arch:SSE /Gy` | 5/5 |
| `/Ox /GS- /Gy` | 5/5 |
| `/O1 /GS- /Gy` | 1/5 |
| `/O2 /Ot- /GS- /Gy` | 5/5 |
| `/O2 /Oi- /GS- /Gy` | 5/5 |
| `/O2 /Oy- /GS- /Gy` | 3/5 |
| `/O2 /Ob0`, `/Ob1`, or `/Ob2` with `/GS- /Gy` | 5/5 each |
| `/O2 /arch:SSE` or `/arch:SSE2` with `/GS- /Gy` | 5/5 each |
| `/O2 /fp:fast` or `/fp:precise` with `/GS- /Gy` | 5/5 each |
| `/O2 /GS /Gy` | 5/5 |
| `/O2 /GS- /Gy-` | 5/5 |

`/O1` changed four bodies: `0x0057B500` compiled to 53 bytes instead of 61, `0x0059CF20` and `0x0059CF60` to 41 instead of 50, and `0x0065FF90` to 30 instead of 36. `/Oy-` changed two: `0x005E3940` gained an EBP frame (47 bytes instead of 44), and `0x0065FF90` gained an EBP frame (39 instead of 36). The other three bodies stayed exact under `/Oy-`.

## What this supports

- `/O2` or `/Ox` is a better fit than `/O1` for these five bodies. This is consistent with speed-oriented optimization but does not distinguish `/O2` from `/Ox` here.
- The no-frame target for `0x0065FF90` specifically matches `/Oy` and not `/Oy-`, which is evidence for frame-pointer omission in that function. Across the five candidates, however, `/Oy-` still matches three, so the sample does not establish a universal setting.
- `/Oi`, `/Ot`, `/Ob`, `/arch`, `/fp`, `/GS`, and `/Gy` made no body-byte difference in this sample. These results cannot identify those options: the functions may not exercise the compiler behavior each switch controls.
- The combined suggested profile matched all five, but because `/O2 /GS- /Gy` alone also matched all five, this sample does not validate the additional flags in that profile.

## Reproduction artifacts

The one-off matrix and complete compiler outputs are in the local ignored workspace at `tmp/flag_probe_20261009/results.json`; the build script is `tmp/run_flag_probe.py`. The inputs, compiler, and reference reports remain local and are not copied into the repository.


## Extended independent sweep

A second, serial run tested eight additional exact adapted candidates from normal CSV entries in the game-code address range. It used nine variants per function (72/72 successful builds): VC8 SP1 `/O2`, `/Ox`, `/O1`, `/Os`, `/O2 /Oy-`, `/O2 /Ot-`, `/O2 /GS`, `/O2 /Gy-`, and VC8 RTM `/O2`.

| Variant | Exact bodies |
|---|---:|
| VC8 SP1 `/O2` | 8/8 |
| VC8 SP1 `/Ox` | 8/8 |
| VC8 SP1 `/O1` | 3/8 |
| VC8 SP1 `/Os` | 3/8 |
| VC8 SP1 `/O2 /Oy-` | 6/8 |
| VC8 SP1 `/O2 /Ot-` | 8/8 |
| VC8 SP1 `/O2 /GS` | 8/8 |
| VC8 SP1 `/O2 /Gy-` | 8/8 |
| VC8 RTM `/O2` | 8/8 |

The eight addresses were `0x004CCC30`, `0x004CCC60`, `0x00538D50`, `0x005487E0`, `0x00581930`, `0x005CDA40`, `0x005E0450`, and `0x0063B6C0`; target body sizes range from 20 to 71 bytes. The selected source variants had already matched their target references under the baseline profile. The run is a small reconstructed-source sample; it does not establish original source provenance.

Together with the five-function probe above, this further favors speed-oriented optimization over `/O1` or `/Os` for these examples. `/O2` and `/Ox`, and VC8 RTM versus SP1, remain indistinguishable in these trials. `/Oy-` loses matches in some functions but not all, while `/GS`, `/Gy`, and `/Ot-` did not change exactness in this sample. The full matrix is in `D:\HP\reconstruction\matching\runs\vc8_expanded_sweep_serial_20261009\summary.json`; the runner is `tmp/run_vc8_expanded_serial.py`.


## Floating-point option probe

An audit of exact adapted candidates in the game-code range found no candidate whose source and exact body could discriminate `/arch` or `/fp` through floating-point arithmetic; the few exact float-related cases contain only loads/stores or zeroing. I therefore tested the non-exact reconstruction of `0x00404BE0` as a sensitivity check only. The reference body is 261 bytes; the baseline `/O2 /GS- /Gy` candidate is 175 bytes and already differs substantially.

| Variant | Candidate body | Exact target |
|---|---:|---|
| Default `/O2 /GS- /Gy` | 175 bytes, x87 | No |
| `/arch:SSE` | 175 bytes, x87 | No |
| `/arch:SSE2` | 346 bytes, SSE | No |
| `/fp:fast` | 117 bytes, x87 | No |
| `/fp:precise` | 175 bytes, x87 | No |
| `/arch:SSE /fp:fast` | 196 bytes, SSE | No |
| `/arch:SSE /fp:precise` | 175 bytes, x87 | No |

The target contains scalar SSE instructions (`movss`, `subss`, `mulss`, `addss`), so the candidate confirms that the selected options can change code generation. The target is compatible with an SSE plus fast-math route or with different source/explicit SIMD, but none of these candidate outputs matches. This is not evidence that the game used `/fp:fast` or `/arch:SSE`; the source reconstruction is not exact. The probe outputs are under `tmp/float_matrix_404be0/`, and its runner is `tmp/float_matrix_404be0.py`.

## Exact floating-point discriminator at `0x0068EC10`

A later scan found a short candidate whose source body reproduces the target's 25 bytes. The C operation is a simple global `float` exchange: save the old global, assign a float argument, and return the saved value as `double`. The target relocations to global `flt_8510B4` were resolved to `0x8510B4` before comparing bytes.

The dedicated probe rebuilt 11 variants with VC8 SP1 14.00.50727.762:

| Variant | Exact 25-byte body? |
|---|---|
| `/O2 /GS- /Gy` | Yes |
| `/O2 /arch:IA32 /GS- /Gy` | Yes |
| `/O2 /fp:precise /GS- /Gy` | Yes |
| `/O2 /arch:SSE` or `/arch:SSE2` | No (29 bytes) |
| `/O2 /fp:fast` | No (17 bytes) |
| `/O2 /fp:strict` | No (34 bytes) |
| `/O2 /arch:SSE /fp:fast` or `/fp:precise` | No |
| `/O2 /arch:SSE2 /fp:fast` or `/fp:precise` | No |

An additional switch sweep on this same source found `/O2` and `/Ox` exact, while `/O1`, `/Os` and `/O2 /Oy-` differed. `/Ob0`, `/Ob1`, `/Ob2`, `/Oi-`, `/Ot-`, `/GS`, `/GS-`, `/Gy-`, `/Gd`, `/Gr`, `/Gz`, `/MD` and `/MDd` all kept this 25-byte body exact, so this function does not identify those switches. Since this function has no stack buffer, `/GS` does not add a cookie here.

This is the first exact-source-byte candidate in the current probes that discriminates `/arch` and `/fp`: the body strongly supports x87/IA32-style code generation and precise floating-point behavior for this compilation. It does not prove a project-wide setting: the source is inferred from IDA pseudocode, and its `semantic_validation` field is false. Source pragmas, explicit code, or per-module options could produce the same result. The reproducible runner is `tmp/probe_exact_float_candidate.py`; raw objects and the relocation-applied matrix are under `tmp/exact_float_candidate_probe/`.

## Exact stack-buffer discriminator for `/GS` at `0x00633050`

The adapted candidate declares a local 12-byte `_WORD[6]`, passes it to an external helper, and returns its first element. The 21-byte target is `83ec0c8d042450e8d0e10a000fb744240483c410c3`. VC8 SP1 `/O2 /GS-` emits the same body after resolving the `REL32` call to `sub_6E122C`. `/O2 /GS` emits 46 bytes and adds a security-cookie read/check; it cannot match the target. The candidate is reported as 100% matched by the local objdiff report (`fn_00633050`, 21/21 bytes).

This is strong evidence that `/GS-` (or an equivalent per-function suppression) was active for this function. The candidate source is reconstructed, so it remains conditional on the inferred local array and helper call being faithful. The compiled variants are in `tmp/gs_probe_00633050/`; the expected target bytes are in `D:\HP\reconstruction\reference\raw\exports\expected\fn_00633050.obj`.

## `memcpy` intrinsic discriminator for `/Oi` at `0x00414170`

The candidate operation is `memcpy((char *)this + 0x90, source, 0xC0)`. The 24-byte target is `568b742408578db990000000b930000000f3a55f5ec20400`, ending in `rep movsd`. With no explicit intrinsic pragma in the candidate, VC8 SP1 `/O2` emits these exact 24 bytes; `/O2 /Oi-` instead emits a 28-byte call to `memcpy`. `/O1` also differs, and `/Ox` matches. Adding `#pragma intrinsic(memcpy)` makes `/Oi-` match again.

This establishes that the target's code is consistent with intrinsic expansion and that disabling `/Oi` changes this candidate under the reconstructed source. It favors `/Oi` enabled (as in the tested `/O2` profile), but cannot rule out a source-level intrinsic pragma. Results and source variants are under `tmp/oi_probe_00414170/`.

### Exact retained `memset` call at `0x0043C2B0`

I reconstructed this function as a C++ constructor that writes vtable `0x832A68`, clears the next field, and calls `memset(this + 8, 0, 0x2C)`. With VC8 SP1 `/O2 /GS- /Gy`, the 36-byte body matches the target exactly after resolving the `REL32` relocation to the `memset` thunk at `0x6B97BC`. Repeating with `/O2 /Oi- /GS- /Gy` yields the same exact 36 bytes and the same call. `/Od /Oi-` differs (52 bytes).

This gives a verified example of a target call to a memory intrinsic that remains a real call under both tested `/Oi` settings. It confirms that retained calls do not establish `/Oi-`; the compiler may simply choose not to expand this 44-byte fill. The candidate and objects are `tmp/fn_43C2B0.cpp` and `tmp/fn_43C2B0_ctor_*.obj`.

### Discriminating real `memcpy` call at `0x006C2030`

This is the stronger `/Oi` probe. The reconstructed C++ method is `S::fn(src) { return memcpy((char *)this + 0x6C, src, 16); }`. Its target body is 51 bytes and calls both the `memcpy` thunk and `__RTC_CheckEsp`. VC8 SP1 `/Od /RTC1` and `/Od /RTC1 /Oi-` both produce a 51-byte body whose non-relocation bytes exactly match the target; the two `REL32` fields point to those same target helpers. `/Od /RTC1 /Oi` emits a 69-byte inline-copy body and does not match. `/O2` and `/RTC1` are incompatible in VC8, so this result is specifically evidence about a non-optimized, runtime-checked unit.

For this unit, the code supports `/Oi-` or equivalent `#pragma function(memcpy)` behavior. The target's `0xCCCCCCCC` stack marker plus `__RTC_CheckEsp` call suggests runtime-check/debug-style compilation; the method is in the high-address third of `.text`. This does not establish the game's global `/Oi` setting, and is not evidence that the main optimized gameplay modules used `/Oi-`. Candidate and verified relocation-aware results are under `tmp/real_memcpy_probe_20261009/`.

I varied the runtime-check switch on this exact candidate as well. `/Od /RTCs /Oi-`, `/Od /RTCsu /Oi-`, `/Od /RTC1 /Oi-`, and `/Od /GZ /Oi-` all reproduce the 51-byte body after resolving the same two relocations. `/Od /RTCu /Oi-` and `/Od /RTCc /Oi-` produce only 34 bytes and omit the target's stack/ESP checks. This confirms stack-variable plus ESP runtime checks for this unit, but does not distinguish `/RTCs`, `/RTC1`, `/RTCsu`, or the deprecated `/GZ` spelling.

## `/Ob` inline probe remains inconclusive

The best local pair found was caller `0x006EB0C9` and small initializer `0x006EDAC0`. The caller candidate matches its 25-byte target under `/O2` when the callee remains external. Combining the inferred initializer and caller into one translation unit for `/Ob0`, `/Ob1`, and `/Ob2` caused broad mismatches (59.375%, 36.875%, 36.875%); the altered ABI and field writes already differed, so those scores cannot be attributed to inlining. No `/Ob` conclusion is drawn. Probe sources and objects are under `tmp/probe_ob_inline_6eb0c9.py` and `tmp/ob_probe_6eb0c9/`.
