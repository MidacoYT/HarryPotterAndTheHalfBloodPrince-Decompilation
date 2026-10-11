# GCC x86 register-convention experiment

## Question

Can a locally available C compiler express the `Hash_ElfPjw` argument ABI
identified by the disassembly and IDA metadata?

## Finding

Yes for the ABI: GCC's x86-32 `regparm(2)` attribute passes the first two
integer arguments in `EAX` and `EDX`; an 8-bit second argument is read from
`DL`. The official GCC x86 attribute documentation specifies the register
order as `EAX`, `EDX`, `ECX`.

The tested compiler is MinGW-w64 GCC 16.2.0 targeting
`i686-w64-mingw32`, obtained as the official MSYS2 package
`mingw-w64-i686-gcc-16.2.0-3-any.pkg.tar.zst`. Its SHA-256 was verified as
`08d09af746f01e0f406e4f5ea41738db3e89f1e17c113185bd80de1ac86d760e`, matching
the hash published by the MSYS2 package page. The package declares
GPL-3.0-or-later. It was extracted under the ignored `tmp/` directory for
testing; it was not installed system-wide.

## Matching result

`Hash_ElfPjw` is 75 bytes in the pinned target object. A C implementation
using `__attribute__((regparm(2)))` compiled successfully to x86 COFF with
this GCC. GCC's register assignments meet the inferred input ABI, but the
generated instructions do not match the target. The first instruction already
differs: GCC begins by reserving stack space and saving `EBP`; the target begins
with `push esi; mov esi,eax`. Runs at `-O0`, `-O1`, `-O2`, `-O3`, `-Os`, and
`-Og` all differed from the target bytes.
An additional matrix followed the IDA pseudocode more closely and added
`-fomit-frame-pointer`; the tested `-O0`, `-O1`, `-O2`, and `-Os` variants
still differed at byte zero.

Therefore this compiler solves the register-passing problem for this function
but is not a matching compiler for the VC8-built target. A project-wide switch
to GCC would not establish exact matches and would likely invalidate current
VC8 matches. No target function was added or counted as matching from this
experiment.

## Clang / LLVM-MinGW follow-up

I also tested Clang 23.1.3 from the upstream LLVM-MinGW 20261006 Windows
archive. The release metadata supplied SHA-256
`317492c456aa27ee607a5919f1d2d38dcdc1112516a24d0bf4b00d078f52d17a`; the
download matched it. The archive's license file states Apache-2.0 with LLVM
Exceptions. The toolchain was unpacked under ignored `tmp/` paths, not
installed system-wide.

Clang accepts the same `regparm(2)` declaration and emits x86 COFF. I tested
`-O0`, `-O1`, `-O2`, `-O3`, `-Os`, `-Oz`, and `-Og` twice: once with the
loop-shaped C implementation, then with the control flow written to follow
the exported IDA pseudocode. None matched the target; the optimized objects
diverged at byte zero. The smallest output was 71 bytes with `-Oz` for the
first source shape, but it still differed from the 75-byte target.

Clang therefore confirms that register-compatible C compilation is available,
but neither current GCC nor current Clang reproduces this VC8 function. The
available evidence does not identify an alternate compiler that will match
the rest of the executable.

Intel's documented IA-32 Windows `__regcall` is not a substitute for this
specific ABI: its first general-purpose argument registers are `ECX`, `EDX`,
`EDI`, and `ESI`, so the pointer would not arrive in `EAX`.

## Open Watcom test

The Open Watcom 2.0 C/C++ User's Guide documents per-function auxiliary
pragmas that assign arguments to specified 32-bit registers, including
`__eax`, `__edx`, and `__esi`. This could express the recovered
`Hash_ElfPjw(char * @ EAX, char @ DL)` ABI. The compiled function confirmed
that a `char` parameter assigned to `__edx` arrives in DL. This is evidence of
ABI expressiveness, not evidence that Watcom was used for this game or that
its code generator can match VC8 output.

The current Windows x64-hosted release asset was downloaded from the official
Open Watcom GitHub release into ignored `tmp/` storage and extracted without
running its installer. Its SHA-256 is
`BEE799B17139489B999195CD8287660A28D39AA934672C53C4B6FDCFBE0CEE41`; the
release API did not publish an asset digest and Windows reports the file as
unsigned. `wcc386` identifies itself as Open Watcom 2.0 beta, dated 2026-10-09.
The pragma successfully passed the pointer in EAX and the byte in DL, but the
optimized output starts `53 51 83 EC 04` (`push ebx; push ecx; sub esp,4`),
versus target `56 8B F0` (`push esi; mov esi,eax`). It emitted 79 bytes versus
75 for the target. Several Watcom optimization options were checked; none
changed the first-byte mismatch. This confirms ABI expressiveness only.

## Borland C++ 5.5.1 test

Borland's documented 32-bit `__fastcall` passes the first arguments in EAX,
EDX, then ECX, matching this function's input register assignment. The
archived Free Command Line Tools 5.5.1 package was extracted into ignored
`tmp/`; the package's SHA-1 matches Internet Archive metadata and its SHA-256
matches an independently published hash (`433B44741F07F2AD673EB936511D498C5A6B7F260F98C4D9A6DA70C41A56D855`).
The compiler identifies as Borland C++ 5.5.1 (2000). It produced OMF objects.

With the source written to follow the IDA pseudocode and declared
`__fastcall`, the `-O2 -6` output was 77 bytes and differed from target at byte
1. Testing non-optimized and optimized modes, including `-k-`, gave a shortest
72-byte output, still different at byte 0 (`53 56` versus target `56 8B`).
Although this is the closest tested alternate compiler so far, it is neither
an exact match nor evidence that Borland was used to build the game.

The test command, from the package's extracted `Bin` directory, was
`bcc32 -c -O2 -6 hash_elfpjw_borland.c`. It exited successfully and produced
an OMF object. `tdump` confirmed the object was translated by Borland 5.5.1;
the OMF `LEDATA` bytes were extracted and compared against the target function
bytes. The `-k-` variant also compiled successfully and measured 72 bytes.

## Reproduction

The tested source used the recovered hash logic and this declaration:

```c
int __attribute__((regparm(2), noinline))
fn_005DACF0(char *s, unsigned char stop);
```

Compile as 32-bit Windows COFF with GCC and compare its function section with
`expected/fn_005DACF0.obj` using objdiff or a byte-level comparator. The local
package and experiment files are in ignored `tmp/` paths and are not project
inputs.

## Sources

- [GCC x86 function attributes](https://gcc.gnu.org/onlinedocs/gcc/x86-Attributes.html)
- [Clang attribute reference](https://clang.llvm.org/docs/AttributeReference.html)
- [MSYS2 package record for i686 GCC](https://packages.msys2.org/packages/mingw-w64-i686-gcc)
- [LLVM-MinGW upstream and release instructions](https://github.com/mstorsjo/llvm-mingw)
- [Intel C++ Compiler Classic calling conventions](https://www.intel.com/content/dam/develop/external/us/en/documents/cpp_compiler_classic_2022.pdf)
- [Open Watcom 2.0 C/C++ User's Guide](https://open-watcom.github.io/open-watcom-v2-wikidocs/cguide.html)
- [Open Watcom V2 official releases](https://github.com/open-watcom/open-watcom-v2/releases)
- [Open Watcom license](https://openwatcom.org/ftp/devel/license-2.pdf)
- [Embarcadero BCC32 calling conventions](https://docwiki.embarcadero.com/RADStudio/Athens/en/Calling_Convention_Options_%28BCC32%29)
- [Borland C++ 5.5.1 archived package](https://archive.org/details/freecommandLinetools)
