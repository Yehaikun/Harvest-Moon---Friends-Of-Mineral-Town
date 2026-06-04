#!/usr/bin/env python3
"""Pre-build validation: script slot sizes, pointer integrity, bad script checks.

Run before `make fomt.gba` to catch errors early instead of discovering
them as white screens.

Usage:
    python3 tools/pre_build_checks.py
    python3 tools/pre_build_checks.py --rom baserom.gba --patches 167:scripts/script_167.mary
"""

from __future__ import annotations

import argparse
import csv
import os
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
from script_slot import DEFAULT_TABLE_OFFSET, DEFAULT_SCRIPT_COUNT, inspect_slot


GBA_ROM_BASE = 0x08000000
MARY_DEFAULT = Path("../stanhash_mary/target/release/mary")

# Known "bad" scripts: mary outputs PARTIAL DECOMPILATION for these.
# They use unsupported script engine features and cannot be round-tripped.
# Tested 2026-06-04: 1296 OK, 32 PARTIAL (out of 1328 total)
# Tested 2026-06-04: all 32 scripts fail compile with "Fatal syntax error"
BAD_SCRIPT_BLACKLIST: set[int] = {
    106, 143, 356, 403, 409, 410, 411, 532, 540, 571, 610, 614,
    617, 620, 623, 625, 629, 632, 635, 638, 640, 644, 647, 650,
    653, 855, 858, 861, 879, 1008, 1013, 1031,
}

# Compiled script filename pattern
SCRIPT_RE = re.compile(r"^(\d+):(.+\.mary)$")


def compile_script(source: Path, mary: Path) -> bytes:
    """Compile a .mary script to bytecode."""
    if not source.exists():
        raise FileNotFoundError(f"source not found: {source}")

    cpp = subprocess.Popen(
        ["cpp", "-P", str(source)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=False,
    )
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as tmp:
        out_path = Path(tmp.name)

    mary_proc = subprocess.Popen(
        [str(mary), "compile", "-o", str(out_path), "--binary"],
        stdin=cpp.stdout,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    assert cpp.stdout is not None
    cpp.stdout.close()
    mary_stdout, mary_stderr = mary_proc.communicate()
    cpp_stderr = cpp.stderr.read().decode("utf-8", errors="replace") if cpp.stderr else ""
    cpp.wait()

    if mary_proc.returncode != 0:
        out_path.unlink(missing_ok=True)
        raise RuntimeError(f"mary compile failed:\n{mary_stdout}{mary_stderr}")

    payload = out_path.read_bytes()
    out_path.unlink(missing_ok=True)
    return payload


def check_patch_slot(
    script_id: int,
    source: Path,
    mary: Path,
    rom: Path,
) -> dict[str, int | str | None]:
    """Check a single patched script fits its ROM slot."""
    result: dict[str, int | str | None] = {
        "script_id": script_id,
        "source": str(source),
        "status": "ok",
        "message": "",
    }

    # Compile the mary script
    try:
        payload = compile_script(source, mary)
    except (FileNotFoundError, RuntimeError) as exc:
        result["status"] = "error"
        result["message"] = str(exc)
        return result

    result["compiled_size"] = len(payload)

    # Check the ROM slot
    try:
        slot = inspect_slot(rom, script_id)
    except (ValueError, FileNotFoundError) as exc:
        result["status"] = "error"
        result["message"] = f"slot inspection failed: {exc}"
        return result

    slot_size = slot.get("slot_size")
    if not isinstance(slot_size, int) or slot_size <= 0:
        result["status"] = "skip"
        result["message"] = f"unbounded slot (slot_size={slot_size})"
        return result

    result["slot_size"] = slot_size
    result["remaining"] = slot_size - len(payload)

    if len(payload) > slot_size:
        result["status"] = "error"
        result["message"] = (
            f"compiled script {script_id} is {len(payload)} bytes, "
            f"but slot is only {slot_size} bytes "
            f"(overflow by {len(payload) - slot_size} bytes)"
        )
    elif len(payload) == slot_size:
        result["message"] = "exact fit (no room for further edits)"
    else:
        result["message"] = f"ok ({slot_size - len(payload)} bytes free)"

    return result


def check_pointer_table(rom: Path) -> list[dict[str, int | str | None]]:
    """Check that the script pointer table points to valid addresses."""
    data = rom.read_bytes()
    results: list[dict[str, int | str | None]] = []
    issues = 0

    for i in range(DEFAULT_SCRIPT_COUNT + 1):
        off = DEFAULT_TABLE_OFFSET + i * 4
        if off + 4 > len(data):
            break
        ptr = struct.unpack_from("<I", data, off)[0]

        if ptr == 0:
            continue  # null pointer (script 0 is always null)

        # Check pointer is in ROM range
        if ptr < GBA_ROM_BASE or ptr > GBA_ROM_BASE + len(data):
            issues += 1
            results.append({
                "index": i,
                "pointer_hex": f"0x{ptr:08X}",
                "issue": "pointer outside ROM range",
            })

    return results


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    parser.add_argument("--mary", type=Path, default=MARY_DEFAULT)
    parser.add_argument(
        "--patches",
        type=str,
        default="",
        help="colon-separated patch specs: 'id:path id:path ...'",
    )
    parser.add_argument("--blacklist", type=str, default="")
    args = parser.parse_args()

    rom = args.rom
    mary = args.mary
    has_errors = False

    # Parse patches
    patches: list[tuple[int, Path]] = []
    for spec in args.patches.split():
        m = SCRIPT_RE.match(spec)
        if m:
            patches.append((int(m.group(1)), Path(m.group(2))))

    # Parse blacklist
    blacklist: set[int] = BAD_SCRIPT_BLACKLIST.copy()
    if args.blacklist:
        for sid_str in args.blacklist.split(","):
            sid_str = sid_str.strip()
            if sid_str.isdigit():
                blacklist.add(int(sid_str))

    # 1. Check patched script slot sizes
    if patches:
        print(f"--- Checking {len(patches)} patched script(s) ---")
        for script_id, source in patches:
            if script_id in blacklist:
                print(f"  SKIP script_{script_id}: blacklisted")
                continue

            result = check_patch_slot(script_id, source, mary, rom)
            sid = result["script_id"]
            status = result["status"]
            msg = result["message"]
            cs = result.get("compiled_size", "?")
            ss = result.get("slot_size", "?")

            if status == "error":
                print(f"  FAIL script_{sid}: {msg}")
                has_errors = True
            elif status == "skip":
                print(f"  SKIP script_{sid}: {msg}")
            else:
                print(f"  OK   script_{sid}: {cs}B -> {ss}B slot, {msg}")

    # 2. Check pointer table integrity
    print(f"\n--- Checking script pointer table ---")
    ptr_issues = check_pointer_table(rom)
    if ptr_issues:
        for issue in ptr_issues[:5]:
            print(f"  FAIL index {issue['index']}: {issue['pointer_hex']} {issue['issue']}")
        if len(ptr_issues) > 5:
            print(f"  ... and {len(ptr_issues) - 5} more pointer issues")
        has_errors = True
    else:
        print("  OK: all script pointers in ROM range")

    # Summary
    if has_errors:
        print("\n❌ Pre-build checks FAILED")
        return 1
    else:
        print("\n✅ Pre-build checks PASSED")
        return 0


if __name__ == "__main__":
    raise SystemExit(main())
