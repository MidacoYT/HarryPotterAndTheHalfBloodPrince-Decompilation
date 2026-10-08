from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXPECTED_SHA256 = "41cbb7ad4b08f6edeb5c2a06aea037d1c0634e9b71df093cc9a26b2287916e10"
RELOCATION_TYPES = {"REL32": 0x0014}


def load_image(path: Path) -> tuple[bytes, int, tuple[int, int, int]]:
    data = path.read_bytes()
    actual_hash = hashlib.sha256(data).hexdigest()
    if actual_hash != EXPECTED_SHA256:
        raise SystemExit(f"Unexpected hp6.exe SHA-256: {actual_hash}")
    if data[:2] != b"MZ":
        raise SystemExit("The target is not a Windows PE executable.")
    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise SystemExit("Invalid PE signature.")
    machine, section_count, _, _, _, optional_size, _ = struct.unpack_from("<HHIIIHH", data, pe_offset + 4)
    if machine != 0x14C:
        raise SystemExit(f"Expected x86 PE (0x14C), got 0x{machine:04X}.")
    optional = pe_offset + 24
    if struct.unpack_from("<H", data, optional)[0] != 0x10B:
        raise SystemExit("Expected a 32-bit PE optional header.")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    section_table = optional + optional_size
    for i in range(section_count):
        off = section_table + 40 * i
        name = data[off:off + 8].split(b"\0", 1)[0]
        if name != b".text":
            continue
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from("<IIII", data, off + 8)
        return data, image_base, (virtual_address, min(virtual_size or raw_size, raw_size), raw_pointer)
    raise SystemExit("The PE executable has no .text section.")


def read_target(image: tuple[bytes, int, tuple[int, int, int]], address: int, size: int) -> bytes:
    data, image_base, (text_rva, text_size, raw_pointer) = image
    rva = address - image_base
    if rva < text_rva or rva + size > text_rva + text_size:
        raise SystemExit(f"Function range 0x{address:X}+0x{size:X} is not in raw .text data.")
    start = raw_pointer + (rva - text_rva)
    return data[start:start + size]


def make_coff(code: bytes, function: dict) -> bytes:
    symbol_names = [function["symbol"]]
    relocations = function.get("relocations", [])
    for relocation in relocations:
        if relocation["symbol"] not in symbol_names:
            symbol_names.append(relocation["symbol"])

    strings = bytearray()
    symbol_fields: list[bytes] = []
    for index, name in enumerate(symbol_names):
        encoded = name.encode("ascii")
        if len(encoded) <= 8:
            name_field = encoded.ljust(8, b"\0")
        else:
            string_offset = 4 + len(strings)
            strings.extend(encoded + b"\0")
            name_field = struct.pack("<II", 0, string_offset)
        section_number = 1 if index == 0 else 0
        symbol_fields.append(name_field + struct.pack("<IhHBB", 0, section_number, 0x20, 2, 0))

    adjusted = bytearray(code)
    relocation_records: list[bytes] = []
    base_address = int(function["address"], 0)
    for relocation in relocations:
        kind = relocation["type"]
        if kind not in RELOCATION_TYPES:
            raise SystemExit(f"Unsupported COFF relocation type: {kind}")
        offset = int(relocation["offset"])
        if offset < 0 or offset + 4 > len(adjusted):
            raise SystemExit(f"Relocation out of range in {function['name']}.")
        if offset == 0 or adjusted[offset - 1] != 0xE8:
            raise SystemExit(f"Expected a direct CALL immediately before relocation at +0x{offset:X}.")
        displacement = struct.unpack_from("<i", adjusted, offset)[0]
        actual_target = base_address + offset + 4 + displacement
        expected_target = int(relocation["target_address"], 0)
        if actual_target != expected_target:
            raise SystemExit(
                f"Call at +0x{offset:X} resolves to 0x{actual_target:08X}, "
                f"expected 0x{expected_target:08X}."
            )
        adjusted[offset:offset + 4] = b"\0\0\0\0"
        symbol_index = symbol_names.index(relocation["symbol"])
        relocation_records.append(struct.pack("<IIH", offset, symbol_index, RELOCATION_TYPES[kind]))

    raw_pointer = 60
    relocation_pointer = raw_pointer + len(adjusted) if relocation_records else 0
    symbol_pointer = raw_pointer + len(adjusted) + 10 * len(relocation_records)
    file_header = struct.pack("<HHIIIHH", 0x14C, 1, 0, symbol_pointer, len(symbol_fields), 0, 0)
    section_header = struct.pack(
        "<8sIIIIIIHHI", b".text", len(adjusted), 0, len(adjusted), raw_pointer,
        relocation_pointer, 0, len(relocation_records), 0, 0x60100020,
    )
    string_table = struct.pack("<I", 4 + len(strings)) + strings
    return file_header + section_header + adjusted + b"".join(relocation_records) + b"".join(symbol_fields) + string_table


def main() -> None:
    parser = argparse.ArgumentParser(description="Build local x86 COFF target objects from a verified hp6.exe.")
    parser.add_argument("--exe", type=Path, required=True, help="path to the user's hp6.exe")
    args = parser.parse_args()
    image = load_image(args.exe)
    manifest = json.loads((ROOT / "tools" / "functions.json").read_text(encoding="utf-8"))
    for function in manifest["functions"]:
        address = int(function["address"], 0)
        code = read_target(image, address, int(function["size"]))
        obj = make_coff(code, function)
        destination = ROOT / function["target_path"]
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(obj)
        print(f"{function['name']}: VA 0x{address:08X}, {len(code)} bytes -> {destination.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
