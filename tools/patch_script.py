#!/usr/bin/env python3
"""Compile a mary script and patch it into a FoMT ROM image."""

from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

from script_slot import DEFAULT_TABLE_OFFSET, inspect_slot, read_symbol_rom_offset


def compile_script(source: Path, mary: Path, output: Path) -> None:
    cpp = subprocess.Popen(
        ["cpp", "-P", str(source)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=False,
    )
    mary_proc = subprocess.Popen(
        [str(mary), "compile", "-o", str(output), "--binary"],
        stdin=cpp.stdout,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    assert cpp.stdout is not None
    cpp.stdout.close()
    mary_stdout, mary_stderr = mary_proc.communicate()
    cpp_stderr = cpp.stderr.read().decode("utf-8", errors="replace") if cpp.stderr else ""
    cpp_status = cpp.wait()

    if cpp_status != 0:
        raise RuntimeError(f"cpp failed for {source}:\n{cpp_stderr}")
    if mary_proc.returncode != 0:
        raise RuntimeError(
            f"mary compile failed for {source}:\n{mary_stdout}{mary_stderr}"
        )
    if not output.exists() or output.stat().st_size == 0:
        raise RuntimeError(f"mary produced no binary output for {source}")


def patch_rom(rom_in: Path, rom_out: Path, script_id: int, compiled: Path, table_offset: int) -> dict[str, int | None]:
    data = bytearray(rom_in.read_bytes())
    slot = inspect_slot(rom_in, script_id, table_offset)
    slot_size = slot["slot_size"]
    if not isinstance(slot_size, int):
        raise RuntimeError(f"script {script_id} has no bounded slot")

    payload = compiled.read_bytes()
    if len(payload) > slot_size:
        raise RuntimeError(
            f"compiled script {script_id} is too large: {len(payload)} bytes > slot {slot_size} bytes"
        )

    rom_offset = slot["rom_offset"]
    if not isinstance(rom_offset, int):
        raise RuntimeError(f"script {script_id} has invalid ROM offset")

    data[rom_offset : rom_offset + len(payload)] = payload
    rom_out.parent.mkdir(parents=True, exist_ok=True)
    rom_out.write_bytes(data)
    return {
        "rom_offset": rom_offset,
        "slot_size": slot_size,
        "compiled_size": len(payload),
        "remaining_bytes": slot_size - len(payload),
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--script-id", type=int, required=True)
    parser.add_argument("--source", type=Path, required=True, help="mary source file")
    parser.add_argument("--rom-in", type=Path, required=True)
    parser.add_argument("--rom-out", type=Path, required=True)
    parser.add_argument("--mary", type=Path, default=Path("../stanhash_mary/target/release/mary"))
    parser.add_argument("--table-offset", type=lambda value: int(value, 0))
    parser.add_argument("--map", type=Path, help="ld map file used to locate gUnk_080F89D4")
    args = parser.parse_args()

    if not args.source.exists():
        raise SystemExit(f"missing script source: {args.source}")
    if not args.rom_in.exists():
        raise SystemExit(f"missing input ROM: {args.rom_in}")
    if not args.mary.exists():
        raise SystemExit(f"missing mary compiler: {args.mary}")

    map_path = args.map
    if map_path is None:
        candidate = args.rom_in.with_suffix(".map")
        if candidate.exists():
            map_path = candidate
    table_offset = (
        args.table_offset
        if args.table_offset is not None
        else read_symbol_rom_offset(map_path)
        if map_path is not None and map_path.exists()
        else DEFAULT_TABLE_OFFSET
    )

    same_path = args.rom_in.resolve() == args.rom_out.resolve()
    with tempfile.TemporaryDirectory(prefix="fomt_script_patch_") as tmp_dir:
        tmp = Path(tmp_dir)
        compiled = tmp / f"script_{args.script_id}.bin"
        compile_script(args.source, args.mary, compiled)
        if same_path:
            tmp_rom = tmp / args.rom_out.name
            result = patch_rom(args.rom_in, tmp_rom, args.script_id, compiled, table_offset)
            shutil.copyfile(tmp_rom, args.rom_out)
        else:
            result = patch_rom(args.rom_in, args.rom_out, args.script_id, compiled, table_offset)

    print(
        "patched script {script_id}: offset=0x{rom_offset:X} size={compiled_size}/{slot_size} remaining={remaining_bytes}".format(
            script_id=args.script_id,
            **result,
        )
    )
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
