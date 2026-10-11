from __future__ import annotations

import json
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = json.loads((ROOT / "tools" / "functions.json").read_text(encoding="utf-8"))


def find_compiler(profile: str | None = None) -> Path:
    if profile == "gcc1310":
        configured = os.environ.get("HP6_GCC1310")
        candidates = [Path(configured)] if configured else []
        candidates.append(Path(r"C:\Qt\Tools\mingw1310_64\bin\gcc.exe"))
        for candidate in candidates:
            if candidate.is_file():
                return candidate
        raise SystemExit("GCC 13.1 x86 compiler not found. Install it or set HP6_GCC1310.")

    if profile == "vc8":
        configured = os.environ.get("HP6_CL_VC8")
        candidates = [Path(configured)] if configured else []
        candidates.append(Path(r"D:\HP\reconstruction\matching\toolchain\vc2005\cl.exe"))
        for candidate in candidates:
            if candidate.is_file():
                return candidate
        raise SystemExit("VC8 compiler not found. Install the licensed toolchain or set HP6_CL_VC8.")

    if profile == "vc71":
        configured = os.environ.get("HP6_CL_VC71")
        candidates = [Path(configured)] if configured else []
        candidates.append(Path(r"D:\HP\reconstruction\matching\toolchain\vc2003-msi-extract\program files\Microsoft Visual C++ Toolkit 2003\bin\cl.exe"))
        for candidate in candidates:
            if candidate.is_file():
                return candidate
        raise SystemExit("VC7.1 compiler not found. Install the licensed toolkit or set HP6_CL_VC71.")

    configured = os.environ.get("HP6_CL") if profile != "latest" else None
    if configured:
        return Path(configured)
    found = shutil.which("cl.exe") if profile != "latest" else None
    if found:
        return Path(found)

    program_files_x86 = Path(os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)"))
    vswhere = program_files_x86 / "Microsoft Visual Studio" / "Installer" / "vswhere.exe"
    if not vswhere.exists():
        raise SystemExit("MSVC x86 compiler not found. Install Visual Studio Build Tools or set HP6_CL.")
    install = subprocess.check_output(
        [str(vswhere), "-latest", "-products", "*", "-requires",
         "Microsoft.VisualStudio.Component.VC.Tools.x86.x64", "-property", "installationPath"],
        text=True,
    ).strip()
    if not install:
        raise SystemExit("Visual Studio installation with the x86 C++ tools was not found.")
    toolsets = Path(install) / "VC" / "Tools" / "MSVC"
    versions = sorted((p for p in toolsets.iterdir() if p.is_dir()), key=lambda p: p.name)
    if not versions:
        raise SystemExit("No MSVC toolset was found in the Visual Studio installation.")
    compiler = versions[-1] / "bin" / "Hostx64" / "x86" / "cl.exe"
    if not compiler.exists():
        raise SystemExit(f"x86 compiler not found: {compiler}")
    return compiler


def compiler_environment(compiler: Path, extra_tools: tuple[Path, ...] = ()) -> dict[str, str]:
    env = os.environ.copy()
    tool_dirs = [compiler.parent, *(tool.parent for tool in extra_tools)]
    env["PATH"] = os.pathsep.join(str(path) for path in tool_dirs) + os.pathsep + env.get("PATH", "")
    include = compiler.parent / "include"
    if include.is_dir():
        existing = env.get("INCLUDE", "")
        env["INCLUDE"] = str(include) + (os.pathsep + existing if existing else "")
    return env


def extract_pe_code(image_path: Path, address: int, size: int) -> bytes:
    image = image_path.read_bytes()
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise SystemExit(f"LTCG output is not a valid PE image: {image_path}")
    section_count = struct.unpack_from("<H", image, pe_offset + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    optional = pe_offset + 24
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    rva = address - image_base
    for index in range(section_count):
        offset = section_table + 40 * index
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from("<IIII", image, offset + 8)
        if virtual_address <= rva and rva + size <= virtual_address + max(virtual_size, raw_size):
            relative = rva - virtual_address
            if relative + size > raw_size:
                break
            return image[raw_pointer + relative:raw_pointer + relative + size]
    raise SystemExit(f"LTCG symbol range 0x{address:08X}+0x{size:X} is not in raw PE data.")


def coff_text(path: Path) -> bytes:
    data = path.read_bytes()
    if len(data) < 20 or struct.unpack_from("<H", data, 0)[0] != 0x14C:
        raise SystemExit(f"Expected an x86 COFF target object: {path}")
    section_count = struct.unpack_from("<H", data, 2)[0]
    optional_size = struct.unpack_from("<H", data, 16)[0]
    section_table = 20 + optional_size
    for index in range(section_count):
        offset = section_table + 40 * index
        name = data[offset:offset + 8].split(b"\0", 1)[0]
        if name == b".text":
            size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
            return data[raw_pointer:raw_pointer + size]
    raise SystemExit(f"Target object has no .text section: {path}")


def coff_text_and_relocs_by_size(path: Path, expected_size: int):
    """Like coff_text, but the object may contain MULTIPLE COMDAT sections
    all literally named ".text" (one per C++ class method in the same
    translation unit, e.g. a real method plus a sibling-class stub used
    only to get the compiler to emit a genuine thiscall call site) --
    picks the one whose size matches, and also returns its relocations."""
    data = path.read_bytes()
    if len(data) < 20 or struct.unpack_from("<H", data, 0)[0] != 0x14C:
        raise SystemExit(f"Expected an x86 COFF target object: {path}")
    section_count = struct.unpack_from("<H", data, 2)[0]
    optional_size = struct.unpack_from("<H", data, 16)[0]
    section_table = 20 + optional_size
    symbol_table_ptr = struct.unpack_from("<I", data, 8)[0]
    symbol_count = struct.unpack_from("<I", data, 12)[0]

    strings_offset = symbol_table_ptr + 18 * symbol_count
    symbols = []
    for i in range(symbol_count):
        off = symbol_table_ptr + 18 * i
        raw_name = data[off:off + 8]
        if raw_name[:4] == b"\0\0\0\0":
            str_off = struct.unpack_from("<I", raw_name, 4)[0]
            end = data.index(b"\0", strings_offset + str_off)
            name = data[strings_offset + str_off:end].decode("ascii", "replace")
        else:
            name = raw_name.split(b"\0", 1)[0].decode("ascii", "replace")
        symbols.append(name)

    candidates = []
    for index in range(section_count):
        offset = section_table + 40 * index
        name = data[offset:offset + 8].split(b"\0", 1)[0]
        if name != b".text":
            continue
        size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
        reloc_ptr = struct.unpack_from("<I", data, offset + 24)[0]
        nreloc = struct.unpack_from("<H", data, offset + 32)[0]
        text = data[raw_pointer:raw_pointer + size]
        relocs = []
        for r in range(nreloc):
            roff = reloc_ptr + r * 10
            vaddr, symidx, rtype = struct.unpack_from("<IIH", data, roff)
            sym_name = symbols[symidx] if symidx < len(symbols) else "?"
            relocs.append({"offset": vaddr, "type": rtype, "symbol": sym_name})
        candidates.append((text, relocs))

    for text, relocs in candidates:
        if len(text) == expected_size:
            return text, relocs
    if candidates:
        return candidates[0]
    raise SystemExit(f"Target object has no .text section: {path}")


def build_ltcg_regarg(unit: dict, output: Path, compiler: Path) -> None:
    """Build an internally-called C function whose final ABI is selected by VC8 LTCG.

    A unit may declare "relocations" (calls to other sub_ functions). Since
    our isolated LTCG probe link can't place those callees at their real
    addresses, the harness source must additionally define a
    __declspec(noinline) stub for every such symbol (matching its real
    signature/convention) so the call genuinely exists in the compiled
    code; we then verify byte-for-byte equality everywhere EXCEPT each
    relocation's 4-byte displacement, and rewrite that displacement to the
    real target before handing the bytes to make_coff (same validate +
    zero + relocation-record mechanism normal non-LTCG calls already use).
    """
    linker = Path(os.environ.get("HP6_LINK", compiler.with_name("link.exe")))
    if not linker.exists():
        raise SystemExit(f"VC8 linker required for LTCG build was not found: {linker}")

    symbol = unit["symbol"]
    function_name = unit["name"]
    if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", function_name):
        raise SystemExit(f"Unsupported LTCG function symbol: {symbol}")
    source = ROOT / unit["source_path"]
    output.parent.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory(prefix=f"{unit['name']}_ltcg_", dir=ROOT / "build") as scratch:
        temporary = Path(scratch)
        object_dir = temporary / "obj"
        object_dir.mkdir()
        harness = temporary / "ltcg_harness.c"
        harness_source = unit.get("ltcg_harness_source")
        if harness_source is None:
            harness_source = (
                f"extern void {function_name}(void **);\n"
                f"void entry(void) {{ void *value = 0; {function_name}(&value); }}\n"
            )
        harness.write_text(harness_source, encoding="ascii")
        env = compiler_environment(compiler, (linker,))
        compile_flags = unit.get("compile_flags", ["/O2"])
        language_flag = "/TP" if unit.get("ltcg_language") == "c++" else "/TC"
        compile_command = [
            str(compiler), "/nologo", "/c", language_flag, "/GL", "/GS-",
            *compile_flags, f"/Fo{object_dir}{os.sep}", str(source), str(harness),
        ]
        subprocess.run(compile_command, cwd=ROOT, env=env, check=True)

        image_path = temporary / "ltcg_harness.exe"
        map_path = temporary / "ltcg_harness.map"
        link_command = [
            str(linker), "/NOLOGO", "/LTCG", "/NODEFAULTLIB", "/SUBSYSTEM:CONSOLE",
            "/ENTRY:entry", "/OPT:NOREF", "/OPT:NOICF", "/INCREMENTAL:NO",
            f"/MAP:{map_path}", f"/OUT:{image_path}",
            *(str(path) for path in object_dir.glob("*.obj")),
        ]
        subprocess.run(link_command, cwd=ROOT, env=env, check=True)

        map_text = map_path.read_text(encoding="ascii", errors="replace")
        map_symbol = unit.get("ltcg_map_symbol", f"_{function_name}")
        match = re.search(
            rf"^\s*\d{{4}}:[0-9A-Fa-f]+\s+{re.escape(map_symbol)}\s+([0-9A-Fa-f]{{8}})\s+f\b",
            map_text,
            re.MULTILINE,
        )
        if match is None:
            raise SystemExit(f"LTCG link map does not contain {symbol} for {unit['name']}.")
        address = int(match.group(1), 16)
        code = bytearray(extract_pe_code(image_path, address, int(unit["size"])))
        expected = coff_text(ROOT / unit["target_path"])
        relocations = unit.get("relocations", [])
        if not relocations:
            if bytes(code) != expected:
                raise SystemExit(
                    f"LTCG output for {unit['name']} does not match target bytes. "
                    f"Built {code.hex()}, expected {expected.hex()}."
                )
        else:
            protected = set()
            for relocation in relocations:
                if relocation["type"] != "REL32":
                    raise SystemExit(f"LTCG regarg calls only support REL32 relocations: {unit['name']}")
                probe_symbol = relocation["symbol"]  # the harness's noinline stub uses the same
                                                      # decorated name as the real callee symbol
                smatch = re.search(
                    rf"^\s*\d{{4}}:[0-9A-Fa-f]+\s+{re.escape(probe_symbol)}\s+([0-9A-Fa-f]{{8}})\s+f\b",
                    map_text, re.MULTILINE,
                )
                if smatch is None:
                    raise SystemExit(f"LTCG link map does not contain stub {probe_symbol} for {unit['name']}.")
                probe_target = int(smatch.group(1), 16)
                offset = int(relocation["offset"])
                if offset == 0 or code[offset - 1] not in (0xE8, 0xE9):
                    raise SystemExit(f"Expected CALL/JMP before relocation at +0x{offset:X} in {unit['name']}.")
                if code[offset - 1] != expected[offset - 1]:
                    raise SystemExit(f"Call opcode mismatch at +0x{offset:X} in {unit['name']}.")
                disp = struct.unpack_from("<i", code, offset)[0]
                actual_probe_target = (address + offset + 4 + disp) & 0xFFFFFFFF
                if actual_probe_target != probe_target:
                    raise SystemExit(
                        f"Call at +0x{offset:X} in {unit['name']} does not resolve to its stub "
                        f"({probe_symbol}); LTCG likely folded/altered the call unexpectedly."
                    )
                expected_target = int(relocation["target_address"], 0)
                real_base = int(unit["address"], 0)
                real_disp = expected_target - (real_base + offset + 4)
                struct.pack_into("<i", code, offset, real_disp)
                protected.update(range(offset, offset + 4))
            for i in range(len(code)):
                if i in protected:
                    continue
                if code[i] != expected[i]:
                    raise SystemExit(
                        f"LTCG output for {unit['name']} does not match target bytes outside "
                        f"relocation windows. Built {bytes(code).hex()}, expected {expected.hex()}."
                    )
        code = bytes(code)

    sys.path.insert(0, str(ROOT / "tools"))
    from extract_target import make_coff

    output.write_bytes(make_coff(code, unit))


def build_cxx_exact(unit: dict, output: Path, compiler: Path) -> None:
    """Compile a VC8 C++ method and normalize its verified .text into the target unit.

    A unit may declare "relocations" for calls to other __thiscall methods.
    MSVC can't declare __thiscall on a free function, so such a call can
    only be reproduced by modeling the callee as a second, sibling class
    with a stub method in the same source (see cxx_thiscall_mp.py) -- a
    real C++ method call, genuinely correct thiscall codegen. Its mangled
    symbol is unpredictable, so "cxx_sibling_classes" maps each
    relocation's canonical project symbol (e.g. "_fn_006E86AA") to the
    sibling class name substring (e.g. "C_fn_006E86AA") that MSVC's name
    mangling always preserves literally, so we can find it in the
    compiled object's own relocation table and validate/repackage it
    under our canonical name instead.
    """
    source = ROOT / unit["source_path"]
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=f"{unit['name']}_cxx_", dir=ROOT / "build") as scratch:
        object_path = Path(scratch) / "candidate.obj"
        env = compiler_environment(compiler)
        flags = unit.get("compile_flags", ["/Od", "/RTC1"])
        subprocess.run(
            [str(compiler), "/nologo", "/c", "/TP", "/GS-", *flags,
             f"/Fo{object_path}", str(source)],
            cwd=ROOT, env=env, check=True,
        )
        relocations = unit.get("relocations", [])
        expected = coff_text(ROOT / unit["target_path"])
        if not relocations:
            code = coff_text(object_path)
            if code != expected:
                raise SystemExit(
                    f"C++ output for {unit['name']} does not match target bytes. "
                    f"Built {code.hex()}, expected {expected.hex()}."
                )
        else:
            code, relocs = coff_text_and_relocs_by_size(object_path, int(unit["size"]))
            code = bytearray(code)
            sibling_classes = unit.get("cxx_sibling_classes", {})
            protected = set()
            for relocation in relocations:
                if relocation["type"] != "REL32":
                    raise SystemExit(f"cxx_exact relocations only support REL32: {unit['name']}")
                offset = int(relocation["offset"])
                needle = sibling_classes.get(relocation["symbol"])
                if needle is None:
                    raise SystemExit(
                        f"No cxx_sibling_classes entry for {relocation['symbol']} in {unit['name']}."
                    )
                matches = [r for r in relocs if r["offset"] == offset and needle in r["symbol"]]
                if not matches:
                    raise SystemExit(
                        f"Call at +0x{offset:X} in {unit['name']} does not resolve to a sibling "
                        f"stub containing {needle!r}; the compiler likely changed how it compiled this."
                    )
                if offset == 0 or code[offset - 1] not in (0xE8, 0xE9):
                    raise SystemExit(f"Expected CALL/JMP before relocation at +0x{offset:X} in {unit['name']}.")
                if code[offset - 1] != expected[offset - 1]:
                    raise SystemExit(f"Call opcode mismatch at +0x{offset:X} in {unit['name']}.")
                # The raw (pre-link) displacement bytes are just whatever
                # placeholder the compiler left for the sibling stub; make_coff
                # re-validates+zeroes this window against target_address using
                # the REAL base address, so write the matching real displacement.
                expected_target = int(relocation["target_address"], 0)
                real_base = int(unit["address"], 0)
                real_disp = expected_target - (real_base + offset + 4)
                struct.pack_into("<i", code, offset, real_disp)
                protected.update(range(offset, offset + 4))
            for i in range(len(code)):
                if i in protected:
                    continue
                if code[i] != expected[i]:
                    raise SystemExit(
                        f"C++ output for {unit['name']} does not match target bytes outside "
                        f"relocation windows. Built {bytes(code).hex()}, expected {expected.hex()}."
                    )
            code = bytes(code)

    sys.path.insert(0, str(ROOT / "tools"))
    from extract_target import make_coff

    output.write_bytes(make_coff(code, unit))


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit("usage: python tools/build.py build/<function>.obj")
    output = (ROOT / sys.argv[1]).resolve()
    unit = next((u for u in MANIFEST["functions"] if (ROOT / u["base_path"]).resolve() == output), None)
    if unit is None or ROOT not in output.parents:
        raise SystemExit("requested object is not listed in tools/functions.json")
    output.parent.mkdir(parents=True, exist_ok=True)
    compiler = find_compiler(unit.get("compiler_profile"))
    if unit.get("compiler_profile") == "gcc1310":
        flags = unit.get("compile_flags", [])
        if not isinstance(flags, list) or not all(isinstance(flag, str) for flag in flags):
            raise SystemExit(f"invalid compile_flags for {unit['name']}")
        env = compiler_environment(compiler)
        subprocess.run(
            [str(compiler), *flags, "-c", "-o", str(output), str(ROOT / unit["source_path"])],
            cwd=ROOT, env=env, check=True,
        )
        return
    if unit.get("ltcg_regarg"):
        build_ltcg_regarg(unit, output, compiler)
        return
    if unit.get("cxx_exact"):
        build_cxx_exact(unit, output, compiler)
        return
    env = compiler_environment(compiler)
    compile_flags = unit.get("compile_flags", ["/O2"])
    if not isinstance(compile_flags, list) or not all(isinstance(flag, str) for flag in compile_flags):
        raise SystemExit(f"invalid compile_flags for {unit['name']}")
    subprocess.run(
        [str(compiler), "/nologo", "/c", "/TC",
         *([] if unit.get("compiler_profile") == "vc71" else ["/GS-"]),
         *compile_flags, f"/Fo{output}", str(ROOT / unit["source_path"])],
        cwd=ROOT,
        env=env,
        check=True,
    )


if __name__ == "__main__":
    main()
