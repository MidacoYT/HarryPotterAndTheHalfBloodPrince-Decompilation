from __future__ import annotations

import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = json.loads((ROOT / "tools" / "functions.json").read_text(encoding="utf-8"))


def find_compiler() -> Path:
    configured = os.environ.get("HP6_CL")
    if configured:
        return Path(configured)
    found = shutil.which("cl.exe")
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


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit("usage: python tools/build.py build/<function>.obj")
    output = (ROOT / sys.argv[1]).resolve()
    unit = next((u for u in MANIFEST["functions"] if (ROOT / u["base_path"]).resolve() == output), None)
    if unit is None or ROOT not in output.parents:
        raise SystemExit("requested object is not listed in tools/functions.json")
    output.parent.mkdir(parents=True, exist_ok=True)
    compiler = find_compiler()
    env = os.environ.copy()
    env["PATH"] = str(compiler.parent) + os.pathsep + env.get("PATH", "")
    subprocess.run(
        [str(compiler), "/nologo", "/c", "/TC", "/O2", "/GS-",
         f"/Fo{output}", str(ROOT / unit["source_path"])],
        cwd=ROOT,
        env=env,
        check=True,
    )


if __name__ == "__main__":
    main()
