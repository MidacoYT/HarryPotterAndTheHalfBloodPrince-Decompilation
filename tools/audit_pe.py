from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import struct
from pathlib import Path
from typing import Any


def cstr(data: bytes, off: int, limit: int = 4096) -> str:
    end = data.find(b"\0", off, min(len(data), off + limit))
    if end < 0:
        raise ValueError(f"unterminated string at 0x{off:X}")
    return data[off:end].decode("ascii", errors="replace")


class PE32:
    def __init__(self, path: Path):
        self.path = path
        self.data = path.read_bytes()
        if self.data[:2] != b"MZ":
            raise ValueError("missing MZ signature")
        self.peoff = struct.unpack_from("<I", self.data, 0x3C)[0]
        if self.data[self.peoff:self.peoff + 4] != b"PE\0\0":
            raise ValueError("missing PE signature")
        h = self.peoff + 4
        (self.machine, self.nsections, self.timestamp, self.symptr, self.nsymbols,
         self.optsize, self.characteristics) = struct.unpack_from("<HHIIIHH", self.data, h)
        self.opt = h + 20
        self.magic = struct.unpack_from("<H", self.data, self.opt)[0]
        if self.magic != 0x10B:
            raise ValueError(f"expected PE32 (0x10B), got 0x{self.magic:04X}")
        self.linker = struct.unpack_from("<BB", self.data, self.opt + 2)
        self.entry = struct.unpack_from("<I", self.data, self.opt + 16)[0]
        self.image_base = struct.unpack_from("<I", self.data, self.opt + 28)[0]
        self.section_alignment, self.file_alignment = struct.unpack_from("<II", self.data, self.opt + 32)
        self.size_image, self.size_headers, self.checksum = struct.unpack_from("<III", self.data, self.opt + 56)
        self.subsystem, self.dllchars = struct.unpack_from("<HH", self.data, self.opt + 68)
        self.ndirs = struct.unpack_from("<I", self.data, self.opt + 92)[0]
        self.dirs = [struct.unpack_from("<II", self.data, self.opt + 96 + 8 * i) for i in range(min(self.ndirs, 16))]
        self.sections = []
        sh = self.opt + self.optsize
        for i in range(self.nsections):
            o = sh + 40 * i
            rawname = self.data[o:o + 8].split(b"\0", 1)[0]
            vsize, va, rawsize, rawptr, relptr, lineptr, nrel, nline, flags = struct.unpack_from("<IIIIIIHHI", self.data, o + 8)
            self.sections.append({"name": rawname.decode("ascii", errors="replace"), "virtual_size": vsize,
                                  "rva": va, "raw_size": rawsize, "raw_offset": rawptr,
                                  "characteristics": flags, "relocation_count": nrel})

    def off(self, rva: int) -> int:
        if rva < self.size_headers:
            return rva
        for s in self.sections:
            span = max(s["virtual_size"], s["raw_size"])
            if s["rva"] <= rva < s["rva"] + span:
                delta = rva - s["rva"]
                if delta >= s["raw_size"]:
                    raise ValueError(f"RVA 0x{rva:X} has no raw file data")
                return s["raw_offset"] + delta
        raise ValueError(f"RVA 0x{rva:X} is outside mapped sections")

    def imports(self) -> list[dict[str, Any]]:
        if len(self.dirs) <= 1 or not self.dirs[1][0]:
            return []
        off = self.off(self.dirs[1][0])
        result = []
        for _ in range(4096):
            oft, stamp, chain, name_rva, first = struct.unpack_from("<IIIII", self.data, off)
            off += 20
            if not (oft or stamp or chain or name_rva or first):
                break
            dll = cstr(self.data, self.off(name_rva))
            thunk = oft or first
            names = []
            for n in range(65536):
                value = struct.unpack_from("<I", self.data, self.off(thunk + 4 * n))[0]
                if not value:
                    break
                if value & 0x80000000:
                    names.append(f"ordinal:{value & 0xFFFF}")
                else:
                    names.append(cstr(self.data, self.off(value) + 2))
            result.append({"dll": dll, "count": len(names), "symbols": names})
        return result

    def exports(self) -> list[str]:
        if not self.dirs or not self.dirs[0][0]:
            return []
        o = self.off(self.dirs[0][0])
        fields = struct.unpack_from("<IIHHIIIIIII", self.data, o)
        n_names, names_rva = fields[7], fields[9]
        out = []
        for i in range(min(n_names, 65536)):
            nrva = struct.unpack_from("<I", self.data, self.off(names_rva + 4 * i))[0]
            out.append(cstr(self.data, self.off(nrva)))
        return out

    def relocations(self) -> dict[str, int]:
        if len(self.dirs) <= 5 or not self.dirs[5][0]:
            return {"blocks": 0, "entries": 0, "absolute": 0, "highlow": 0, "other": 0}
        rva, size = self.dirs[5]
        end = self.off(rva) + size
        pos = self.off(rva)
        blocks = entries = absolute = highlow = other = 0
        while pos + 8 <= end:
            page, blocksize = struct.unpack_from("<II", self.data, pos)
            if blocksize < 8:
                break
            blocks += 1
            for i in range((blocksize - 8) // 2):
                typ = struct.unpack_from("<H", self.data, pos + 8 + 2 * i)[0] >> 12
                entries += 1
                if typ == 0: absolute += 1
                elif typ == 3: highlow += 1
                else: other += 1
            pos += blocksize
        return {"blocks": blocks, "entries": entries, "absolute": absolute, "highlow": highlow, "other": other}

    def debug(self) -> list[dict[str, Any]]:
        if len(self.dirs) <= 6 or not self.dirs[6][0]:
            return []
        o = self.off(self.dirs[6][0]); size = self.dirs[6][1]
        out = []
        types = {1:"COFF",2:"CodeView",4:"Misc",5:"Exception",6:"Fixup",7:"OmapToSrc",8:"OmapFromSrc",9:"Borland",10:"Reserved10",11:"CLSID",12:"VCFeature",13:"POGO",14:"ILTCG",15:"MPX",16:"Repro"}
        for p in range(o, o + size - 27, 28):
            _, _, _, _, typ, data_size, data_rva, data_ptr = struct.unpack_from("<IIHHIIII", self.data, p)
            item: dict[str, Any] = {"type": types.get(typ, str(typ)), "size": data_size}
            if typ == 2 and data_ptr and data_size >= 4:
                sig = self.data[data_ptr:data_ptr + 4]
                if sig == b"RSDS" and data_size >= 24:
                    age = struct.unpack_from("<I", self.data, data_ptr + 20)[0]
                    pdb = cstr(self.data, data_ptr + 24)
                    item.update({"format":"RSDS", "age":age, "pdb_basename":Path(pdb.replace("\\", "/")).name})
                elif sig == b"NB10" and data_size >= 16:
                    age = struct.unpack_from("<I", self.data, data_ptr + 12)[0]
                    pdb = cstr(self.data, data_ptr + 16)
                    item.update({"format":"NB10", "age":age, "pdb_basename":Path(pdb.replace("\\", "/")).name})
                else:
                    item["signature"] = sig.decode("ascii", errors="replace")
            out.append(item)
        return out

    def summary(self) -> dict[str, Any]:
        imports = self.imports()
        strings = [s for s in re.findall(rb"[\x20-\x7e]{5,}", self.data)]
        marker_hits = {}
        patterns = {
            "msvc_runtime_dll": rb"(?i)\b(?:msvcr|msvcp|vcruntime|msvcp_win)[0-9_]*\.dll\b",
            "cxx_frame_handler": rb"__CxxFrameHandler[0-9]*",
            "security_cookie": rb"__security_cookie|__security_check_cookie",
            "rtti_type_descriptor": rb"\.\?AV[^\x00]{1,80}",
            "pdb_path_marker": rb"RSDS|NB10",
        }
        blob = b"\n".join(strings)
        for key, pattern in patterns.items():
            vals = sorted({m.decode("ascii", errors="replace") for m in re.findall(pattern, blob)})
            marker_hits[key] = vals[:40]
        return {
            "file": self.path.name,
            "file_size": len(self.data),
            "sha256": hashlib.sha256(self.data).hexdigest(),
            "pe": {"machine": f"0x{self.machine:04X}", "format": "PE32" if self.magic == 0x10B else f"0x{self.magic:04X}",
                   "coff_timestamp_unix": self.timestamp, "linker_version": f"{self.linker[0]}.{self.linker[1]:02}",
                   "image_base": f"0x{self.image_base:08X}", "entry_rva": f"0x{self.entry:08X}",
                   "section_alignment": self.section_alignment, "file_alignment": self.file_alignment,
                   "size_of_image": self.size_image, "size_of_headers": self.size_headers,
                   "checksum": f"0x{self.checksum:08X}", "subsystem": self.subsystem,
                   "dll_characteristics": f"0x{self.dllchars:04X}", "number_of_data_directories": self.ndirs},
            "sections": self.sections,
            "data_directories": [{"index": i, "rva": f"0x{rva:08X}", "size": size} for i,(rva,size) in enumerate(self.dirs) if rva or size],
            "imports": imports,
            "import_dll_count": len(imports),
            "import_symbol_count": sum(x["count"] for x in imports),
            "exports": self.exports(),
            "base_relocations": self.relocations(),
            "debug_directories": self.debug(),
            "markers": marker_hits,
        }


def main() -> None:
    parser = argparse.ArgumentParser(description="Audit PE32 metadata without third-party packages.")
    parser.add_argument("--exe", type=Path, default=os.environ.get("HP6_EXE_PATH"), help="path to hp6.exe (or HP6_EXE_PATH)")
    args = parser.parse_args()
    if not args.exe:
        parser.error("provide --exe or set HP6_EXE_PATH")
    print(json.dumps(PE32(args.exe).summary(), indent=2))


if __name__ == "__main__":
    main()
