# Engineering notes

## 2026-10-11 — `tools/own_decompiler.py` correctness review

The tool is an experimental Capstone transliterator for PE32 x86, with
instruction-level CFG analysis and C emission. It is useful for producing
recompilation candidates. Accepting a function does not establish semantic
equivalence or recover its original ABI.

This pass preserved the public five-element `transliterate()` result and
the command-line interface. It changed these correctness checks:

- Jump tables require an unsigned `cmp`/guard sequence: `ja N` admits
  `N + 1` entries, while `jae N` admits `N`. The index must remain unchanged;
  table entries must target instructions; direct branches and other resolved
  tables must not bypass the guard.
- Writes to `AL`, `AH` and `AX` preserve the remaining bits of `EAX`. CFG
  input analysis now accounts for those preserved bits. Full-register
  `xor reg, reg` no longer creates an unnecessary input parameter.
- Unknown entry flags survive CFG merges and back edges. Calls invalidate
  the known flag producer; `setcc` and `cmovcc` also require known flags.
- Integer comparisons preserve 8/16/32-bit signedness. `jnl` and `jnle`
  aliases now agree with `jge` and `jg`. Signed branches after arithmetic
  are rejected when their overflow flag is not modeled.
- Deferred comparisons reject subregister overwrites and potentially
  aliasing memory stores. A `setcc` that is itself a branch destination
  cannot be consumed as part of a preceding compare.
- Shift counts are masked to five bits; arithmetic right shifts sign-extend
  byte and word operands before C promotion.
- Stack alignment makes the old ESP depth unknown. Incomplete disassembly
  and reachable fallthrough beyond the function boundary are rejected.

### Validation

Python 3.11, Capstone 5.0.7, Windows x86 execution and the existing VC8
toolchain were used. The suite contains 29 Python regression cases plus one
optional native comparison test. All 30 passed with the native test enabled.

The native test compiles 70 synthetic snippets in both `/Od` and `/O2` and
compares their generated C with the exact original instruction bytes in
MSVC naked wrappers. Inputs cover all pairs of values 0 through 255 and a
set of 17 boundary values, including negative 32-bit representations and
shift counts at and above 32. This validates those snippets only; no full
game scan or project-wide byte-match report was regenerated.

Run the portable regression checks from the repository root:

```powershell
python -m unittest discover -s tools/tests -v
```

To enable the native check, set `HP6_CL_VC8` to the existing x86 `cl.exe`
before running that command. Its sibling `link.exe` is required. The native
test creates temporary files under `tmp/` and removes its own directory
afterward. No game data or downloads are required.

### Remaining limitations

Call conventions, pushed arguments, callee clobbers and return values still
use heuristics. Stack locals are independent C objects and do not yet model
overlapping accesses or the original contiguous frame. SIMD state across
branches and preserved upper lanes need further work. EFLAGS are tracked by
producer rather than independently by flag bit, and general signed integer
overflow in emitted arithmetic is not yet modeled throughout the emitter.

These limitations are why the module description now explicitly labels the
output as a candidate. Byte matching and semantic checks remain separate
requirements. The stricter checks may reduce accepted candidate counts.

Instruction reference: [Intel IA-32 and Intel 64 manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html),
particularly the Jcc, CMP, TEST and SAL/SAR/SHL/SHR entries.

## 2026-10-11 — Follow-up blocker audit

Ran `tmp/own_decompiler_review/audit_blockers.py` against the pinned game
image and the current manifest, excluding the 2,368 exact functions in the
existing report. This was a translation audit, not a new compiler search or
rebuild. Details are in `tmp/own_decompiler_review/blockers_current.json`.

Of 8,623 unresolved functions, 1,647 produced translation candidates. Their
current matcher routes are 869 LTCG candidates, 83 ordinary C candidates,
453 rejected by `multi-live-in`, and 242 rejected by
`stack-args-with-live-in`. Translation success is not semantic validation.

Largest first-error families include unknown CFG stack state (1,156
functions / 758,061 bytes), dangling compare/test (778 / 215,035), and
unknown EBP anchor (1,496 / 60,523). There are 560 first failures on indirect
call cleanup. Across all unresolved functions, 1,461 contain x87 instructions
and 392 contain FS-segment operands; these overlapping features are not
additional first-error counts. Removing one error may expose another.

Concrete observations for the next implementation pass:

- `fn_0040BF70` uses `lea ebp, [eax + 8]`: EBP is a general pointer here,
  while the translator treats this LEA as an attempted stack-frame setup.
- `fn_00401DE0` aligns ESP to 16 bytes and retains EBP for restoration.
  A symbolic aligned-frame base is needed to represent its local accesses.
- The manifest range for `fn_00405BA0` ends at a `pop edi`, before a return.
  Function boundary validation must precede attempts to match such ranges.
- Synthetic `push 1; call eax; add esp, 4; ret` raises
  `indirect-call-no-cleanup`: `has_cleanup` requires an absent
  `call_arg_bytes` entry, although the preceding push grouping created it.
- A translated function using ECX plus `[esp + 4]` is rejected by the matcher.
  Standard ABI recovery must be attempted before treating mixed inputs as
  an unsupported custom calling convention.

Recommended sequence: repair the demonstrated call/EBP defects and matcher
ABI routing; validate boundaries; introduce symbolic frame identities and
explicit flag values per CFG block; add x87/SIMD/exception patterns; guide
compiler candidate search with instruction-level differences and the real
call context. Verify relocation targets and generated switch-table contents
when reporting normalized byte matches.

ABI references: [Microsoft `__thiscall`](https://learn.microsoft.com/en-us/cpp/cpp/thiscall?view=msvc-170)
and [LTCG calling-convention optimization](https://learn.microsoft.com/en-us/cpp/build/reference/ltcg-link-time-code-generation?view=msvc-170).

### 2026-10-11 — Continued fixes and verification

Added conservative call cleanup matching: an `add esp, N` counts as caller
argument cleanup only when it agrees with the backward group of 32-bit pushes.
This reduced first-error `call:cleanup-argument-mismatch` from 222 to 189
functions in the unresolved-function audit. FS-segment moves now report the
explicit SEH/TLS reconstruction blocker instead of looking like ordinary
unsupported memory operands.

Added `tools/repair_function_boundaries.py`. It scans the pinned executable,
uses recursive reachable decoding bounded by known function entries, and
writes candidates to `tmp/own_decompiler_review/boundary_candidates.json`
without editing `tools/functions.json`. The current scan found 483 extents
that continue beyond their manifest sizes; each still needs a successful
compile-and-byte comparison before adoption.

After these fixes, the full read-only audit translated 4,223 of 8,623
unresolved functions (up from 4,198 in the immediately preceding audit).
That describes transliteration only. The project report remains at 2,368 of
10,991 exact functions (21.5449%); no full matcher rebuild was run and none of
the eight exploratory compiler attempts found an exact match. The largest
remaining first-error groups include unknown stack state (880), SEH/TLS
semantics (356), undefined flag inputs (318), indirect branches (267), and
COMISS condition tracking (260).

The regression suite now has 52 passing tests, including the optional native
VC8 comparison against original x86 snippets. Python syntax checks also pass.

### 2026-10-11 — Call cleanup and stack-slot disambiguation

Refined ABI cleanup classification: a stack-slot access between `CALL` and
`ADD ESP, N` now makes a mismatched adjustment ambiguous, so the translator
ignores it instead of rejecting the function as an argument mismatch. A
matching push count still qualifies as caller cleanup even when a stack slot
is used first. This avoids confusing late local-frame releases with argument
cleanup while preserving call argument inference. The final audit reports 178
`call:cleanup-argument-mismatch` functions (down from 203) and 4,672
transliterated functions out of 8,628 unresolved. The exact-match report
remains 2,363 / 10,991 (21.4994%); transliteration alone does not count as a
match.

The regression suite now has 65 passing tests and Python syntax checks pass.
A fresh VC8 exact-match sweep of 100 newly eligible translated candidates found
no additional byte-identical functions. Two former cleanup-mismatch examples
now advance to later blockers (`x87:stack-underflow` and
`cfg:unknown-stack-state`), confirming this was a misclassification fix rather
than a source-match gain.

### 2026-10-11 — Plain-C exact match batches

The first 100 plain-C candidates yielded four exact matches; the next 100
yielded one. All five candidates were added, compiled through the normal build
path, and verified in objdiff. The report is now 2,368 / 10,991 exact functions
(21.5449%). One C++ free-function relocation needed an explicit symbol mapping
in `cxx_sibling_classes` for the project build verifier.

The cumulative plain-C sweep covered 472 eligible attempts (including one
candidate already staged from the preceding batch) and found 12 new exact
functions relative to the starting report. Seven more exact candidates from
the expanded sweep were staged and built successfully, bringing objdiff to
2,375 / 10,991 (21.6086%). All 66 regression tests and Python syntax checks
pass. The LTCG route still needs separate work; its first 100 candidates did
not produce a new match.

## 2026-10-12 — x87 CFG depth tracking, call/register-permutation retries, instruction gaps

Added a CFG-based forward dataflow for x87 stack DEPTH (`_x87_cfg_depths`,
`_x87_push_pop_delta`, both in `own_decompiler.py`), mirroring the existing
`esp_depth`/`ebp_anchor` merge logic: every block entry re-synchronizes
`fpu.stack` to persistent `__fp87_0..7` slots instead of carrying over
whatever Python expression list happened to survive the previous block in
linear scan order. A live x87 value may now legitimately cross a `jmp`/`jcc`
(spilled into those slots first) and, after confirming a real counter-example
in this binary (`fn_00670B20`, an argument kept alive across a plain `call`
via `fst` without pop), also across a `call` -- `x87:live-stack-at-merge` and
`x87:live-stack-across-control-transfer` no longer exist as hard rejections
for either case. One real bug found mid-implementation: the depth probe
primed its stack with 8 dummy entries "to avoid underflow," but 8 is already
the real x87 maximum, so any `fld` in a probed block immediately hit a false
`stack-overflow` and the whole block's depth came back `None` (unknown).
Fixed by priming at 4 instead.

Added `fist`/`fistp` (own_float.py): a plain C truncating `(int)` cast of a
float/double, on any x87-only target, compiles to the exact
save/modify-to-truncate/restore control-word bracket around a real `FISTP`
-- there is no other way to get C's truncate-toward-zero semantics out of
x87 hardware. `fnstcw`/`fldcw` are therefore modeled as pure no-ops: nothing
needs to reproduce them by hand, the compiler regenerates the identical
bracket itself from the cast. Tried (and abandoned) forcing this bracket via
`#pragma runtime_checks` and `/QIfist`: neither applies here. Separately,
confirmed with `/RTCs` is HARD command-line-incompatible with every `/O`
level in this VC8 (`D8016`), so a `cmp ebp, esp` + `call __RTC_CheckEsp`
probe (/RTCs stack-corruption instrumentation, target address `0x6F35A0`
verified against real call sites, not guessed from a name) is modeled as a
dead no-op instead -- nothing downstream ever reads the flags it would set.
`/RTCs` paired with each `/O` level was still added to `FLAG_SETS` for
functions that don't hit this exact probe. A real function in this family
(`fn_006C4370`) still doesn't byte-match even under `/Od /RTCs`: our
candidate comes out ~3.4x the target's size, because `/RTCs` inserts one
poison-fill per DECLARED stack variable and this translator declares far
more small per-register locals than the original source likely had one
variable for. Unresolved; would need fewer, coarser-grained local
declarations to ever match a `/RTCs` function's byte count, not a flag or
pragma change.

Added the classic (`fcom`/`fcomp`/`fcompp`) x87 compares plus `fnstsw ax`
(own_float.py's `consume_fnstsw`, own_decompiler.py's dispatch): these write
C0/C2/C3 into the FPU status word, not EFLAGS directly, and this binary's
real idiom is `fcompp; fnstsw ax; test ah, mask; jcc` (confirmed at
`0x68bfa8` and others) -- not the `sahf` bridge. `fnstsw ax` now packs the
pending comparison into AH bits 0/2/6 exactly where a real `FNSTSW AX`
would put them; the existing generic `test`/`sahf` lowering handles
everything downstream with no FNSTSW-specific logic of its own.

Extended `_retry_with_register_rename`'s "pure register permutation"
diagnostic (already used for the LTCG path, credited there to
isledecomp/reccmp's "swap register allocations" trick) to the plain
(non-LTCG) path too, plus an isledecomp-style "effective match" side log
(`tmp/autodecomp/effective_matches.jsonl`) for near-misses that differ only
by a consistent GP-register renaming but where the rename retry itself
didn't find a literal byte match -- never counted in `report.json`, purely
for prioritizing follow-up. Measured yield on this binary is low so far (1
genuine pure-permutation near-miss in ~1,300 sampled candidates, and that
one specific case wasn't resolved by renaming -- VC8's choice there tracked
data-flow shape, not identifier spelling).

Added `movdqa`/`movdqu` (were classified as SSE-safe but never actually
lowered), general-register-pair `pxor` (same-register zeroing was already
handled; the general form now bridges through `_mm_castsi128_ps`/
`_mm_castps_si128` the same way `movsd`/`addsd`-family already did for
`_pd`), and the `fiadd`/`fisub`/`fisubr`/`fimul`/`fidiv`/`fidivr`
integer-memory-operand x87 arithmetic family. Checked this binary directly
via disassembly before building any of these (several candidate additions
from this same pass -- genuine SSE2 scalar-double arithmetic, `movsd`
`xmm,xmm`/mem, XMM-register `pxor` -- turned out to have zero real
occurrences anywhere in the executable once checked; kept the code since
it's harmless, but it isn't exercised here).

Found, not yet fixed: `unsupported-mem:pop` (e.g. `fn_006DBDA1`). The
argument-push grouping in `own_abi.py` pairs an unrelated pair of local
stack-reservation pushes (`push ecx; push ecx`, releasing no real values)
together with a genuine call-argument push that comes later, so `stack_depth`
drops by 16 instead of 4 by the time a real cleanup `pop ecx` after the call
is reached, landing exactly in the reserved-slot special case
(`_resolve_frame_slot`'s `[0,4)` "saved return address" check) instead of a
real local. Root-caused via a one-line trace of every `_resolve_frame_slot`
call; not fixed this pass -- `argument_pushes`/`deferred_call_groups` are
sensitive, already-iterated-on machinery, and this needs a careful look at
why the grouping treats a push separated by intervening non-push
instructions (`mov`, `lea`) as part of the same group before changing it.

Also unresolved, lower priority, no repro collected yet this pass: `shrd`,
`cmpeqps`, `movdqa`/`stosw`-adjacent remainders, and a segment-prefixed
`movsd` destination (`dword ptr es:[edi]`).

### Same day, follow-up — the other `/RTCs` ESP-check shape

`unsupported-register:esp` (4 remaining real instances, e.g. `fn_006C5530`)
turned out to be a second, narrower variant of the same `/RTCs` probe: a
`cmp ebp, esp` right before `__RTC_CheckEsp` isn't the only shape --
`fn_006C5530` snapshots ESP into a scratch callee-saved register
(`mov esi, esp`) across exactly ONE indirect call (bracketing just that
call site, not the whole function), then does `cmp esi, esp` right before
the same `__RTC_CheckEsp` call. Generalized the existing dead-probe
recognizer into two small helpers in `own_decompiler.py`:
`_is_dead_rtc_esp_check` (now matches `cmp <any-reg>, esp` immediately
before a known-void CRT target, not just `ebp`) and
`_is_dead_rtc_esp_snapshot` (`mov <reg>, esp` is itself a no-op too, IF its
only later use within a bounded window is a matching check on that exact
register with no intervening write -- confirmed safe against the real
instruction sequence by hand before generalizing, not guessed). All 4 real
remaining instances in the 500-sample now translate cleanly;
`unsupported-register:esp` is at zero in that sample, up from 385 to 389
compiled candidates with 0 regressions/errors (matched count unchanged --
these are `/RTCs` functions, so they hit the already-documented
"/RTCs inserts one poison-fill per declared local, we declare more locals
than the original" wall above, not a new blocker).

### Same day, follow-up — small instruction-support gaps

Added, each checked against a real disassembled occurrence in this binary
first: `shrd`/`shld` (double-register shift, immediate or `cl` count;
flags raise `flags:undefined` if actually needed rather than guessing
CF/OF, which this translator doesn't compute for them); `stosw`/
`rep stosw` (word-width sibling of the existing `stosd`/`__stosd` support,
using a new `__stosw` intrinsic declared in the same three header-injection
sites as `__stosd`); `cmpeqps` and its seven CMPPS-predicate siblings
(`cmpltps`/`cmpleps`/`cmpunordps`/`cmpneqps`/`cmpnltps`/`cmpnleps`/
`cmpordps`, added together since they share one dispatch table entry each
at zero extra cost once one is wired in); `movmskps` (`_mm_movemask_ps`,
the GP-register-destination pairing that commonly follows a `cmpps`); and
`punpcklbw`/`punpckhbw`/`punpcklwd`/`punpckhwd` (integer interleave,
bridged through `_mm_castsi128_ps`/`_mm_castps_si128` the same way
`pxor`'s general form already is).

500-sample run: 0 regressions/errors, compiled-candidate count up from 389
to 397. `unsupported-insn:movq` (MMX `mm0..mm7`, a separate, undeclared
register family -- real cost to add properly, not attempted this pass) and
`pmullw` (newly exposed behind the now-fixed `punpcklbw`, in the same two
functions) remain. `hlt` at `0x64929e` is a boundary problem, not an
instruction gap: the bytes right after it decode as nonsense
("inc ebp; hlt; add byte ptr [eax], al..."), consistent with the function's
real end being earlier and this being alignment padding after it.

### Same day, follow-up — `xchg`, and three more boundary false starts

Added `xchg` (register/register, register/memory, either operand order):
a plain three-step swap through a fresh declared temp, real atomicity not
modeled since nothing here is concurrent. Checked against a real example
(`0x68ba70`, a small allocator-looking routine) first; it now translates
cleanly (not yet byte-matched, but reaches the compiler). 500-sample run:
0 regressions/errors, compiled-candidate count up from 397 to 398.

Checked `esp-from-unset-ebp` (1 instance, `0x56fb55`) and
`flags:undefined@...:cf` (1 instance, `0x491277`) by hand: both are, like
`hlt` above, boundary false starts rather than translator gaps. The first
function's manifest start address lands AFTER a real `push ebp; mov ebp,
esp` prologue it must have had (it later reads `[ebp+8]` with no `ebp`
anchor ever established in view); the second's manifest start address
lands exactly on an `adc byte ptr [esp+0x48], dl` as literally the first
decoded instruction, needing an incoming carry flag no real function entry
could provide. Logged here rather than attempted -- this is squarely
`repair_function_boundaries.py`/`match_boundary_candidates.py` territory.

Also checked `unsupported-insn:pushfd` (1 instance, `0x6ea8c0`): it's the
textbook CPUID-availability probe (`pushfd; pop eax; xor eax, 0x200000;
push eax; popfd; pushfd; pop eax; xor eax, ecx` -- toggle EFLAGS bit 21 and
see if it "stuck"), confirmed by re-running after the `xchg`/other fixes
and watching it progress one instruction further to a bare `cpuid`. Left
unmodeled: `pushfd`/`popfd` would need to push/pop a real, persistent,
frame-slot-backed EFLAGS-like value through the exact same stack-slot
machinery normal register pushes use, which is a materially bigger and
more sensitive change than this pass's other additions for one confirmed
occurrence so far.

### Same day, follow-up — MMX, the `own_abi.py` reservation-pushes bug, and a general pxor

**`own_abi.py` reservation-push bug, fixed.** Root-caused via a one-line
trace of every `_resolve_frame_slot` call (see the earlier "found, not yet
fixed" entry): `argument_pushes`'s backward scan has no way to tell "two
pushes of the same scratch register, back-to-back, are a cheap `sub esp, 8`
substitute whose garbage VALUES are read back only via a later `lea`
address" from "two real call arguments." Added `_is_reservation_pair_push`
(true for a non-callee-saved-named push immediately adjacent to another
push of the identical register) and applied it in two places: filtering
`argument_pushes`'s own group before storing it, and excluding such pushes
from `deferred_call_groups`'s `reserved_elsewhere` guard (which otherwise
also misfired, refusing to treat a real cleanup `pop` as this call's own
once the group was corrected). Fixed 2 of the 3 real
`unsupported-mem:pop` instances in the 500-sample; the third is a
different, unrelated problem (another boundary false start). No regression
risk to the existing 2,398 already-matched functions: this logic only runs
for `missing_normal_functions()`'s unmatched set, never re-touching
committed `src/*.c`.

**`xchg`** (register/register, register/memory): a three-step swap through
one fresh declared temp.

**MMX, built from scratch.** Added an `mm0..mm7` register class parallel
to `XMM` (`MM`, plus `RegState.note_mm_read/note_mm_write`, `mm-live-in-
not-supported` for any read before this function's own write -- no MMX
calling-convention path is modeled, unlike XMM's). Verified FIRST, before
writing any of the transliteration code, that a plain `__m64` struct-copy
through a pointer cast really does compile to a real `MOVQ` under VC8
(it does: confirmed by direct compile + COFF disassembly, `0F 6F`/`0F 7F`).
Added: `movq` (mm/mm, mm/mem, mem/mm); `movd` (mm<->GP32/mem via
`_mm_cvtsi32_si64`/`_mm_cvtsi64_si32`); `movdq2q`/`movq2dq` (xmm<->mm 64-bit
transfer, `_mm_movepi64_pi64`/`_mm_movpi64_epi64`); a shared
`_PACKED_INT_BINOP` table covering `paddb/w`, `psubb/w`, `pand`, `por`,
`pandn`, the saturating adds/subs, `pcmpeq*`/`pcmpgt*`, `pmaddwd`, and
`pack*` -- each entry pairs the MMX intrinsic with its SSE2 `__m128i`
equivalent (bridged through `_mm_castps_si128`/`_mm_castsi128_ps` the same
way `pxor`'s general form already was), since several of these opcodes
(`pmullw`, `punpcklbw`/`hwd`/`lwd`, `pand`, `por`, ...) turned out to be
used on BOTH register families in this binary, sometimes in the very same
function; and `_PACKED_INT_SHIFT` for the immediate-count shifts
(`psrlw/d/q`, `psllw/d/q`, `psraw/d`, plus the SSE2-only whole-register
`psrldq`/`pslldq`). General (non-same-register) `pxor` extended the same
way, for both XMM and MM.

Found one real VC8 header bug along the way, the same style of surprise as
the earlier `/RTCs`/optimization-incompatibility and `/QIfist` findings:
`_mm_packus_pi16`/`_mm_packsswb`/`_mm_packssdw` (the "_mm_" spelling of
MMX pack-with-saturation) hit a genuine `C2718` alignment error specific
to those three intrinsics, reproduced in isolation with a minimal test
file unrelated to anything this translator generates. The older legacy
`_m_packuswb`/`_m_packsswb`/`_m_packssdw` spelling of the exact same
operations compiles cleanly; used those three specifically, `_mm_*` for
everything else (validated individually by direct compile before use, not
assumed from naming symmetry).

500-sample run: 0 regressions/errors throughout every step. Net for this
whole follow-up pass: compiled-candidate count up from 398 to 406; `movq`,
`pmullw`, `pxor-general`, and (2 of 3 instances of) `unsupported-mem:pop`
are now at zero in this sample.

### 2026-10-13 — Self-regression in `_is_dead_rtc_esp_snapshot`, fixed

After codex's indirect-branch/calling-convention/SEH pass changed the
manifest and re-sampling the same 500-function draw, `esp-from-unset-ebp`
jumped from 1 to 5. Traced with a per-instruction dump of both RTC helper
predicates (not just the failing one) and found a real self-inflicted
regression: `_is_dead_rtc_esp_snapshot` treats ANY "mov <reg>, esp" as a
candidate scratch snapshot, including `ebp` -- and a plain function's own
perfectly ordinary epilogue probe (`cmp ebp, esp; call __RTC_CheckEsp`)
looks, to that function's generic "same register, no intervening write"
forward scan, exactly like proof that the PROLOGUE's `mov ebp, esp` (real
frame-pointer establishment, always handled by its own dedicated check
elsewhere in the dispatch) was just disposable scratch too. Confirmed
concretely on `fn_006C10B0`, a plain /RTCs function with a real EBP frame.
Fixed by excluding `ebp` from the snapshot predicate's candidate
registers -- it can never legitimately be "scratch" for this specific
probe shape, since the dedicated ebp/esp-pair check already owns that
case. Re-sampled 500: `esp-from-unset-ebp` back down to 4 (the 3 that
remain are, like before, genuine boundary false starts -- confirmed by
hand on one, e.g. `0x55092A` decodes to nonsense
("sub dword ptr [eax+0x7D01B000], eax...") as its very first instruction).

This is a reminder to re-run the standing regression sample after ANY
manifest-affecting change lands from the other side, not just after this
session's own edits -- a changed `functions.json` changes which addresses
`missing_normal_functions()` even draws for the same random seed, so a
skip-reason count moving is not proof either way on its own without
checking a concrete example.

### Same day, follow-up — `fucom*`, `pmulhw`/`punpck*dq`/`punpck*qdq`, `stosb`, `xadd`

Added: `fucom`/`fucomp`/`fucompp` (folded into the existing `fcom` family
-- the "unordered" forms only differ from the plain ones in QNaN exception
behavior, which this translator never raises either way, so they share the
exact same lowering); `pmulhw` and `punpckldq`/`punpckhdq` (added to the
shared `_PACKED_INT_BINOP`/punpck tables, same pattern as the existing
entries); `punpcklqdq`/`punpckhqdq` (SSE2-only whole-64-bit-lane unpack, no
MMX form -- `(None, "_mm_unpacklo_epi64")`-style entries, same table);
`stosb`/`rep stosb` (byte-width sibling of `stosd`/`stosw`, a new
`__stosb` intrinsic declared in the same three header-injection sites);
`xadd`/`lock xadd` (capstone folds the `lock` prefix into the mnemonic
string itself) as a three-step swap-and-add through one fresh temp, real
atomicity not modeled since nothing here is concurrent.

500-sample run: 0 regressions/errors. Translated-candidate count up from
404 (after the `_is_dead_rtc_esp_snapshot` fix) to 408; `fucompp`,
`pmulhw`, `stosb`, and `unsupported-insn:lock xadd` are now at zero.

## 2026-10-13 - Repeated arguments and x87 call-result lifetime

Reviewed the additions made since the preceding pass. Repeated scratch-register
pushes were being classified as local reservations merely because the two
register names were identical. This dropped genuine f(x, x) arguments in 57
manifest functions. Reservation recognition now requires an EBP prologue and
address-taking of both local slots before the first call; the fn_006DBDA1 case
remains supported. EBP saved in the prologue and restored with LEAVE is also
excluded from call arguments.

Tested the 20 shortest affected functions. Six matched, including three already
matched functions. Three newly matched sources were integrated and rebuilt:
fn_006B49AC (22 bytes, VC8 /O1 /Oy-), fn_006DCB08 (22 bytes, same options), and
fn_004291A0 (57 bytes, VC8 C++ /O2). Reinstating the old reservation heuristic
made all three fail the same exact matcher. The project builder then reproduced
all 101 bytes, with call relocation symbols and target addresses validated.

The x87 _CI helper lowering now evaluates each call once and retains its result.
Previously, fn_00402A70's FST followed by a comparison duplicated fmod() in the
generated source. That real function now contains one fmod evaluation. It and
fn_00634CC0 still do not match exactly; this is a candidate correctness fix,
not a claimed byte-match gain. Storing an x87 value as a C double still requires
byte verification because compiler rounding and spilling can differ.

Validation: 3 new call-value lifetime regressions, 30 translator tests and
9 ABI/validation tests passed. Targeted game results are recorded locally under
tmp/resume_claude_targeted/. The regenerated objdiff report has 2,401/10,992
matched functions and 29,929/2,530,025 matched code bytes. No full candidate
compilation batch was run.

### 2026-10-13 - Eight-byte output objects and direct member calls

Extended the EBP reservation-pair recognition to cover slots overwritten before
the call, and eight-byte output objects whose address is passed and whose two
halves are read afterwards. fn_006E7FA4 now translates past its prior
unsupported-mem:pop blocker; it still differs when recompiled.

Added a narrowly recognized C candidate for the complete import-output wrapper:
one local eight-byte value, one pointer argument, optional low-dword zeroing,
and an EDX:EAX return. Both fn_006D985D (27 bytes) and fn_006D98C2 (23 bytes)
match using VC8 /O1 /Oy-. The candidate uses a normal unsigned __int64 C local
and a dllimport declaration. The shared absolute-import compile/link helper
verifies the linked instructions and absolute IAT slot against the executable.
Existing six-byte import thunks retain the same path and pass regression tests.

Added direct-thiscall candidates for callee-pop calls preceded by preparation
of ECX. C++ method declarations preserve the object argument, and structured
branch candidates recover the original block layout where the goto form did
not. Call relocation targets remain validated. fn_0069B690 is an already
integrated reference that this translator route can now reproduce.

On 25 previously unmatched eligible functions, six newly match:
fn_006B6585 (25), fn_006B6543 (30), fn_0069BA80 (35), fn_0069E140 (35),
fn_0069CF10 (42), fn_006D79CE (44). All six fail when the new member-call route
is disabled. Their sources and the two output wrappers were integrated and
rebuilt with tools/build.py; both COFF bytes and relocation records match their
target objects. Eight newly matched functions account for 261 bytes.

Validation: 55 tests passed (5 call-value lifetime, 2 native output/member,
30 translator, 7 import slots, 2 opaque callee, 9 ABI/validation). Regenerated
report.json: 2,409/10,992 functions and 30,190/2,530,025 code bytes matched.
Targeted probe results and baseline comparisons are in tmp/blockers_next/.
These routes do not solve arbitrary LTCG register ABIs, all SEH, general
indirect jumps, or every EDX:EAX return shape.

### 2026-10-13 - LTCG ABI, SEH and indirect dispatch audit

Indirect jumps: the remaining twelve six-byte FF 25 import tail thunks were
compiled and linked against their original absolute IAT slot. All twelve
matched every target byte and were integrated/rebuilt (72 new matched bytes).
They are fn_006B9172, fn_006B9178, fn_006B92AA, fn_006B93A4, fn_006B93F4,
fn_006B9400, fn_006B9406, fn_006B97BC, fn_006B9C24, fn_006F2B54,
fn_006F3630 and fn_006F51A8.

The more complex fn_006B643E dispatch is a validated two-stage switch:
24 original inputs index a byte map at 0x006B64CE; its 14 values index the
address table at 0x006B6496. The resolver now checks the unsigned guard,
all 24 byte-map entries and all 14 in-range target instruction addresses.
The function translates, but C compiler variants tried still differ in
bytes. Its earlier `or eax, -1` also no longer creates a false EAX input.
Bare seven-byte jump-table dispatch entries such as fn_0056EDE0 have no
guard in their recorded extent; these may be fragments of larger functions
and are deliberately not treated as standalone safe switches.

SEH: the old 362-function FS-chain blocker category now has 331 translation
successes with current code. The 15 shortest translated SEH functions were
compiled and compared; none matched. A real fn_006D3630 additionally needed
XORPD, now lowered via _mm_setzero_pd (isolated VC8 COFF: 66 0F 57 C0 C3).
Its full function still differs. A VC8 /O2 /EHsc C++ try/catch probe produced
the characteristic push -1 / push handler / FS chain, but included an EBP
prologue absent from fn_006324C0. VC8 /GL plus LTCG retained that EBP
prologue, and VS2012 /O2 /EHsc did too. Exact SEH code generation remains
unresolved; FS access translation alone is insufficient.

LTCG register convention: fn_004050E0 has EDX and EAX live inputs, one
stack input, and a callee-pop RET 4. C probes with VC8 /GL /LTCG using a
three-argument stdcall signature and several caller shapes generated different
register allocations and instruction order; none matched its 11 bytes. This
specific mixed register/stack ABI remains unproven. The probe files are under
tmp/three_walls/ltcg_abi/.

Validation: three two-stage/OR/XORPD regressions and the 30 existing
translator tests pass. Every integrated thunk was rebuilt and its COFF code
and relocations compared with the target. report.json now records 2,421 of
10,992 functions and 30,262 of 2,530,025 code bytes exactly matched.

Register-target tail jumps: a GP register `jmp` is now a CFG tail exit and
lowers as a C function-pointer call; unresolved memory jumps still require
switch validation. `fn_0066F830` was compiled with VC8 `/O2` as a C++
thiscall method and matched all 40 bytes. Its COFF object was rebuilt against
the recorded target, and the report was regenerated: 2,422 / 10,992 exact
functions, 30,302 / 2,530,025 exact code bytes. The same lowering translates
`fn_0053F240` and `fn_00670380` but does not match them. In `fn_0053F240`,
the target retains the function pointer in EDX and sets ECX as a thiscall
argument before `jmp edx`; the plain function-pointer C emits `jmp eax` and
omits that ECX setup. A fastcall/thiscall pointer probe restores the ECX setup
and matches the target length (54 bytes), but still selects EAX for the jump
pointer. `fn_00670380` is 51 versus 56 bytes under its closest C candidate;
it folds the final memory load into `jmp [ecx+0x14]` and omits a register
setup before the earlier virtual call. These are remaining codegen constraints,
not unvalidated CFG coverage. The focused regressions and existing decompiler
tests pass.

A further audit of the previous indirect-branch failures found 55 functions
whose blocker was specifically a GP-register jump. All 55 now transliterate.
The 12 shortest were sent through the compiler matcher: only the already
integrated `fn_0066F830` matched. Tail-only functions previously had no
`RET` immediate and therefore skipped thiscall/fastcall hypotheses; the ABI
candidate logic now retains those hypotheses when the pop size is unknown.
For example, `fn_00658220` then compiles to the target's 20-byte length and
correct ECX setup but uses EAX instead of EDX for its final jump. This makes
the register-allocation wall measurable on a real affected function. The
36 focused and existing decompiler tests pass after this change.

SEH shape refinement: the first generic C++ `try/catch` probes above were
misleading for `fn_006324C0`. A VC8 `/O2 /EHsc` constructor with a member
whose destructor must run if a later call throws, and a destructor with a
member/base destructor after a throwing call, both emit the exact first
29-byte `push -1; push handler; fs:[0]`/`push ecx; push esi; mov esi, ecx;
mov [esp+4], esi` prologue shape seen in that function, without an EBP
frame. Source probes are `tmp/three_walls/seh_ctor_member_throw.cpp` and
`tmp/three_walls/seh_dtor_member.cpp`. The target's specific vtable writes,
unwind handler relocation, call, and epilogue still need a complete C++
object model and linker mapping before it can be counted as exact. This
identifies the relevant VC8 EH convention rather than attributing its
prologue difference to an unknown compiler version.

### 2026-10-13 - Fresh remaining-blocker audit

The current report has 8,570 nonmatching functions (2,499,723 code bytes).
A fresh read-only pass over their recorded extents translated 7,654 functions
(1,859,132 bytes, 74.4% of the remaining bytes). Thus successful control-flow
translation is not the same as reproducing code generation. Only 14 of the
nonmatching units currently have a checked-in source path.

The leading translation failures are 222 incomplete instruction tails
(189,507 bytes), 214 functions falling through their recorded end (212,114
bytes), 144 unresolved indirect branches (40,889 bytes), and 84 conditional
branches outside their recorded extent (40,136 bytes). These three boundary
categories together account for 520 functions / 441,757 bytes. In the real
`fn_00408F10`, the recorded extent ends in `83 87 C0`, mid-instruction;
`fn_00405BA0` ends at `pop edi` without its exit. Boundaries therefore need
repair before further C matching. An unresolved `fn_00420380` switch has a
valid six-entry table but an alternate predecessor jumps to the table without
the local `cmp eax,5` guard, requiring path-sensitive range proof.

SEH/SSE: the earlier `fn_006D3630` translation failed VC8 compilation with
C2718 because `_mm_castpd_ps(_mm_setzero_pd())` passes an aligned `__m128d`
by value. Lowering `xorpd xmm0,xmm0` as an lvalue reinterpretation now
compiles and produces exact isolated bytes `66 0F 57 C0 C3`. The real 78-byte
SEH function now compiles as 69 bytes but still differs from its C++ EH
prologue/body. The focused compiler regression and all 36 decompiler tests
pass. No additional exact function is claimed from this fix.

Current prioritization: recover/repair function extents; resolve guarded and
nested switch tables with path-sensitive CFG facts; model native C++ EH
metadata and object lifetime; then address LTCG free-register and mixed
stack/register ABIs. Compiler flag sweeps alone did not reproduce the shown
EDX-versus-EAX tail jumps or the 11-byte mixed-ABI `fn_004050E0`.

### 2026-10-13 - Repaired extents, guarded switches, and one exact C++ EH body

The bounded recursive decoder identified 479 manifest extents that stopped
before a reachable return and before the next known function entry. All 479
were extended; their target COFF objects were regenerated from the pinned
executable. This adds 3,820 bytes to the recorded total. Two functions
previously counted on a truncated prefix, `fn_00433240` and `fn_004B30C0`,
were rebuilt and checked on their full 82- and 28-byte extents; both remain
exact. Of the 479 repaired functions, 425 now translate. Two of the first
20 previously unsourced translations matched with VC8 LTCG and opaque
callees: `fn_005FB7E0` (55 bytes, two REL32 calls) and `fn_00504F10`
(66 bytes, one REL32 call). Both are integrated and their rebuilt COFF bytes
and relocation records equal the targets. Another 80 repaired, previously
unsourced translations were tried without an exact match.

The switch resolver now proves a constant bypass path into a guarded jump
table (`fn_00420380`: six targets, other path sets index to 3) and accepts
a register-held constant guard (`fn_0043B5D0`: seven- and eight-entry tables).
It rejects a corrupted bypass index and a corrupted bound that would run
one address table into the next. Both real functions translate, but their
full C compilations still differ in bytes.

For `fn_006324C0`, a VC8 `/O2 /EHsc` virtual C++ destructor plus a base
destructor emits the exact 70-byte instruction sequence. The only linker
fields are the EH handler at +3 (DIR32, 0x006F7848), derived vtable at +31
(DIR32, 0x008426B0), and call at +44 (REL32, 0x00631FF0). `build_cxx_exact`
now checks each relocation type and source symbol before normalizing it,
and rejects a C++ COMDAT with an incorrect full length. The rebuilt object
matches the target bytes and all three relocations. This resolves the
previously open SEH example; it does not imply that every C++ EH function
shares this destructor shape.

The mixed-register LTCG `fn_004050E0` remains unresolved: 48 targeted
VC8 `/GL` probes spanning argument permutations, `/O1` and `/O2`, and four
caller shapes produced no exact match. The current report records 2,425 of
10,992 functions and 30,506 of 2,533,845 code bytes exactly matched.
Forty-four focused and existing tests pass.

### 2026-10-13 - Batch recovery of EH frame thunks

The unpaired inventory contained 1,433 small C++ EH frame thunks. They read or
form a value relative to their parent's EBP frame, optionally adjust and push
it, then jump or call a handler. Standalone C functions cannot express this
calling context. `tools/recover_eh_funclets.py` recognizes the supported
instruction patterns from the hash-checked executable and emits symbolic
MASM source. The pass covered 370 eight-byte direct tail jumps, 733 related
pointer-adjustment or call shapes, 164 wider-displacement or indirect IAT
jumps, and 166 prefixed push or frame-shim shapes. Direct transfers carry
REL32 records; indirect IAT jumps carry DIR32 records.

`tools/build.py` assembles each source with VC8 MASM and verifies full length,
all bytes outside relocations, and the exact relocation type, position, and
symbol. It resolves the destination and compares the complete normalized
COFF object. The batch builder passed 1,433/1,433 functions. The separate
near miss `fn_006BE590` matched after correcting its return type from
`unsigned char` to `unsigned int`, giving the target's `movzx eax` instead of
`mov al`; its rebuilt object is 12/12 bytes exact. The regenerated report
records 3,859/10,992 functions and 48,505/2,533,845 code bytes exact: a gain
of 1,434 functions and 17,999 code bytes over the prior report.

### 2026-10-13 - Largest unmatched functions

The 25 largest unmatched manifest functions were probed with the real
executable and VC8 `/O2`. None matched exactly. `fn_00498680` had an
eight-byte truncated tail in the manifest: its corrected extent is 15,490
bytes, and the translator now emits 4,461 statements. The generated code
compiles to 25,080 bytes, so its control flow and data expressions remain
substantially different from the target. Among other compilable examples,
`fn_004C2290` generated 13,643 versus 9,344 target bytes, and
`fn_005FB820` generated 5,563 versus 4,951 bytes.

The switch resolver now handles an index in EAX mapped into EDX before a
two-entry address table in `fn_0058E7B0` (6,010 bytes). This function
translates in full to 2,785 statements, but VC8 compilation exposes a join
where one call to `fn_00535F40` receives one reconstructed argument rather
than five. The actual disassembly reaches the call from branches that each
prepare five arguments. Another switch in `fn_004473A0` (5,504 bytes) now
resolves four entries after proving that an external call preserves the
constant switch bound in EDI. Its translation remains blocked by frame
alignment handling. Both table fixes reject deliberately corrupted bounds or
map entries; 46 focused tests pass.
The refreshed local report remains at 3,865/10,992 exact functions and
48,657 exact code bytes; correcting the truncated large-function extent
changes the total-code denominator to 2,533,853 bytes.

### 2026-10-13 - Joined call arguments and large x87 blocks

`fn_0058E7B0` now compiles after recognizing its two alternate paths that
each prepare four stack arguments before a common fifth push and call.
The recognizer requires two other five-argument calls to the same target and
matching push/fstp shapes on both arms. A corrupted arm is rejected by the
regression test. The VC8 `/O2` output is 8,552 versus 6,010 target bytes.

The x87 CFG-depth probe now tries each physically possible starting depth,
because a fixed four-value prime falsely overflows blocks with five genuine
pushes. That allows `fn_006A93C0` (8,420 bytes) to translate. Its C++
candidate also now compiles with an `extern "C"` variadic declaration for a
cdecl callee reached with different observed arities. The best tested VC8
output is 9,689 bytes with `/O2 /Oy-`; `/O2` alone emits 10,099 bytes.
`fn_00570EC0` initially still had an x87-depth conflict across a larger
control-flow join. Its known `fld; fsqrt` helper at `0x00401020` returns on
ST(0); accounting for that return after a prior pop resolves the join. The
10,368-byte function now translates in full and compiles. COFF reading also
selects the section containing the named function: the first C++ `.text`
section was a 15-byte auxiliary, while this function's actual compiled
section is 16,038 bytes. The same correction measures `fn_004E1140` as
15,642 versus 9,620 target bytes, rather than an unrelated 18-byte COMDAT.
These changes produced no new exact match. The focused suite runs 50 tests:
49 pass and one is skipped in this environment. Tested `/O1`, `/O2`, `/Ox`,
`/Od`, and `/O2 /Oy-` variants still leave `fn_00570EC0` at least 4,932
bytes too large and `fn_004E1140` at least 5,248 bytes too large.

## Small-function batch triage

The 3,000 smallest unmatched functions (up to 113 bytes) were translated and
compiled with VC8. The `/O2` pass found 232 exact matches. A sweep of six
other flag sets across 1,558 initial near misses found 46 more, mostly with
`/O1 /Oy-`. All 278 were promoted to `src/`, rebuilt with the project
builder, and compared as complete normalized COFF objects against their
targets, including all recorded call relocations. The other outcomes were
1,512 compiled nonmatches, 1,121 LTCG-only ABI cases, and 89 unsupported
translations. The new exact matches add 11,600 code bytes, bringing the
report to 4,143 of 10,992 exact functions and 60,257 of 2,533,853 bytes.
The report update retained measures for old units from the prior full
objdiff report and changed only the newly verified exact units.

## LTCG and indirect-dispatch follow-up

All 1,121 LTCG-only cases from that triage were retried with the linked
register-argument probe. Twenty-four reproduced the complete target bytes;
their C bodies, harnesses, and call relocation metadata were registered and
rebuilt through `build_ltcg_regarg`. All 23 blocked indirect-dispatch units
were recovered as readable MASM instruction sources. The assembler builder
now verifies multiple direct-call relocations in one unit; the 92-byte
switch dispatcher `fn_0056ED40` is included. Two more same-size near misses
matched after source-level branch restructuring. String-copy and `repz ret`
translation support unblocked ten additional functions, though none of those
compiled to exact bytes in the tested modes. A final sweep of five more VC8
flag sets over 1,504 unsourced nonmatches found no further exact function.

The 3,000-function batch therefore added 327 exact functions overall. The
incrementally updated report shows 4,192/10,992 exact functions and
61,804/2,533,853 exact code bytes. Existing report measures outside the
new verified units remain from the previous full objdiff generation.

## 2026-10-14 - Large-function instruction reconstruction

The 492 unmatched functions over 1,024 bytes accounted for 1,110,200 recorded
bytes, while none matched. Translation triage handled 416 of them but VC8
compilation of the generated C produced no exact body in `/O2` or the tested
alternate optimization flags; 204 needed the separate LTCG ABI path. This
showed that the current C lifter could not rapidly close the large-byte gap.

`tools/recover_large_asm.py` now emits readable MASM from each instruction in
the pinned executable, with symbolic local labels and verified REL32 records
for direct external transfers. It preserves exact alternate encodings for
alignment LEAs, certain x87 self-operations, and wide immediate forms with
small `db` directives beside decoded instruction comments. Among the first
486 exact bodies, 349 of 266,248 instruction lines used these directives;
the rest are assembler instructions. The pass rejects undecoded tails and
does not treat an approximate C compilation as exact.

Six recorded extents ended midway through an instruction before a visible
epilogue. Linear decoding up to the first subsequent return, bounded by the
next known function entry, established new extents for `fn_00471AF0` (2,674),
`fn_00617E20` (3,302), `fn_0046CF90` (3,383), `fn_00680F60` (3,964),
`fn_005C7DA0` (7,360), and `fn_0064E7F0` (7,629). Their newly covered bytes
were read from the same pinned executable, assembled, and verified.

`tools/promote_large_asm.py` independently rebuilt all 492 sources with VC8
MASM through `build_asm_funclet`, checking full length, every nonrelocated
byte, relocation symbol/type/offset/target, and the normalized COFF object.
All 492 passed and were promoted to `src/`. The report now reads
4,684/10,992 exact functions and 1,172,054/2,533,903 exact code bytes
(42.61% of functions; 46.25% of bytes). This is exact assembly
reconstruction, not recovery of the original C or C++ source. The C lifter's
large-function code generation remains a separate unsolved problem.

## 2026-10-14 - C pseudocode for the 492 large functions

Exported one C candidate per large ASM function to `research/large_c/` without
replacing the exact ASM build inputs. IDA 9.1 Hex-Rays decompiled 484
functions; `own_decompiler.py` translated the 8 functions IDA could not
decompile. The export manifest records 9 IDA extent disagreements and 2
functions with IDA stack warnings. All 492 files were checked present and
nonempty. VC8 `/O2` initially compiled 7 of the 8 translator fallbacks; the
remaining indirect `__thiscall` cast was lowered through a C-compatible
`__fastcall` pointer with an unused EDX argument. All 8 now compile, but none
matches the target bytes. The 484 IDA outputs are pseudocode using IDA's types
and unresolved symbols; the following compile probes do not count any as a C match.
The byte-exact report therefore remains unchanged.

### C compile probes after the export

The indirect `__thiscall` fallback was lowered to a C-compatible
`__fastcall` pointer with a dummy EDX argument, so all 8 fallback files now
compile with VC8 `/O2`; none matches. A separate probe translated IDA's
address-named globals and calls in the 100 Hex-Rays bodies with plain C ABIs.
Eighteen compiled with `/O2`, none exact. Seven alternate optimizer flag sets
on those 18 made 126 more attempts, none exact. `fn_006E384B` under `/O1`
had the closest mnemonic sequence (89.36%) but differed in stack frame size
and remained 29 bytes short. The probe results are in
`research/large_c/probe_plain_abi.jsonl` and `probe_flags.jsonl`; all exact ASM
sources and the report remain unchanged.

## 2026-10-14 - Full re-triage of the remaining unmatched pool

Re-ran the C-lifter pipeline over all 6,308 functions that still had no
matching source, instead of only the 3,000 smallest. The triage translated
6,068 and blocked 240. A six-worker VC8 `/O2` ABI pass then compiled every
translated body under each plausible convention; three functions matched
exactly and were promoted. A nop-padding live-in fix in
`own_decompiler.py` (see below) unblocked 33 further units from the LTCG
deferral path; one matched. The full LTCG register-argument matcher,
including structured-if restructuring and register-permutation retries, ran
over the remaining 3,026 deferred units (about 4.5 CPU-hours across eight
workers) and produced one exact match. The heavyweight `try_match` path,
which additionally restructures branches and probes alternate flag sets,
was run over the 88 same-size near misses and produced none. Five new
exact matches were promoted in total, taking the report from 4,684 to 4,689
functions and from 1,172,054 to 1,172,768 matched code bytes.

### Where the remaining pool is stuck

The 3,026-function LTCG-deferred pool holds 702,848 bytes and is now
measured as exhausted at a 0.03% exact rate. Sampling and classifying its
entries shows why. Many "functions" are not function entries at all: they
are mid-function fragments and shared tails whose first instruction reads
an incoming register (`lea eax, [esi+0x38]`, `cmp eax, 0x63`,
`mov eax, [ebp-0x60]`) because a preceding block in the enclosing function
set that register up. At least 307 of the sampled entries begin with such
a read before any prologue. These units can never match as standalone
compilations. The rest are genuine entries whose live-in registers are
argument channels the plain cdecl/stdcall path cannot express.

The 3,039-function no-match pool (574,988 bytes) compiles but differs in
bytes. Diagnosing the 88 same-size cases instruction by instruction shows
the differences are real codegen divergence, not translator bugs. The
dominant first-difference shapes are callee-saved push ordering
(`push esi` versus `mov eax, [esp+4]`), inverted branch polarity after a
shared-tail join, register allocation for argument loads, and XMM register
selection. In the closest cases the reconstructed statements are correct
but VC8 `/O2` reoptimizes them differently than the original compiler did:
for `fn_005BAC30` the C source reproduces `if (esi == 0) goto L;` exactly,
yet the optimizer constant-propagates the branch fact into the shared
block and folds `[esi+0x50]` into the absolute address `[0x50]`, which the
original code does not do. Statement-level reconstruction cannot control
that divergence. The 192 units whose every ABI attempt failed to compile
and the ~600 units within ±16 bytes of their target show the same shapes.

### Nop-padding live-in fix

VC8 emits `lea eax, [eax]` and `lea ebx, [ebx]` as function-alignment
padding. Because such an instruction reads and writes the same register
with no net effect, the live-in analysis counted the register as
read-before-definition, which pushed otherwise ordinary cdecl/stdcall
functions into the LTCG-only deferral path. `_cfg_live_in_registers` now
discards the read for `lea X, [X]` (no displacement, no index) and for
`mov X, X`, and the statement lowering records the write before emitting
the self-assignment so the padding stays visible to byte comparison. The
fix unblocked 33 of the 3,026 deferred units; one matched exactly. It is a
correctness fix regardless of the match yield, because the previous
analysis reported those functions with a wrong signature.

### Tooling changes

`match_triage_fast.py` now derives its scratch directory from the output
file name so several workers can run concurrently. `match_triage_deep.py`
gained `--results`, `--same-size-only`, and `--worker/--workers` so the
heavyweight matcher can be pointed at any no-match pool and parallelized.
`promote_triage_exact.py` now also writes the verified base object to the
unit's `base_path`, so later incremental report updates can compare base
against target without a full clean rebuild. `promote_ltcg_exact.py` gained
`--results` and now skips units that already have a source instead of
aborting, so it can be re-run as new exacts accumulate.
`update_report_exact.py` skips already-marked units before verifying and
trusts the promotion-time check for LTCG register-argument units, whose
plain base object legitimately differs from the LTCG-shaped target.

### Measurement

The report was updated incrementally from the verified objects rather than
regenerated with `objdiff-cli report generate`, because a full regeneration
requires a `base.obj` for every sourced unit and 2,668 of those build
artifacts are absent. The incremental path marks only newly verified
units and leaves every other unit's previous measures untouched. The
resulting report is version 2 with all 10,992 units present.
