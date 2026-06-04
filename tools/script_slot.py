#!/usr/bin/env python3
"""Inspect FoMT event-script slots in a ROM image."""

from __future__ import annotations

import argparse
import json
import struct
from pathlib import Path


GBA_ROM_BASE = 0x08000000
DEFAULT_TABLE_OFFSET = 0x0F89D4
DEFAULT_SCRIPT_COUNT = 1328


def _read_u32(data: bytes, offset: int) -> int:
    if offset < 0 or offset + 4 > len(data):
        raise ValueError(f"offset out of range: 0x{offset:X}")
    return struct.unpack_from("<I", data, offset)[0]


def gba_addr_to_rom_offset(addr: int) -> int:
    if addr < GBA_ROM_BASE:
        raise ValueError(f"not a ROM address: 0x{addr:08X}")
    return addr - GBA_ROM_BASE


def inspect_slot(
    rom_path: Path,
    script_id: int,
    table_offset: int = DEFAULT_TABLE_OFFSET,
    script_count: int = DEFAULT_SCRIPT_COUNT,
) -> dict[str, int | bool | None]:
    if script_id < 1 or script_id > script_count:
        raise ValueError(f"script id must be in 1..{script_count}: {script_id}")

    data = rom_path.read_bytes()
    entry_count = script_count + 1
    table_size = entry_count * 4
    if table_offset + table_size > len(data):
        raise ValueError(
            f"script table 0x{table_offset:X}+0x{table_size:X} is outside {rom_path}"
        )

    ptr = _read_u32(data, table_offset + script_id * 4)
    if ptr == 0:
        raise ValueError(f"script {script_id} has a null pointer")

    rom_offset = gba_addr_to_rom_offset(ptr)
    if rom_offset >= len(data):
        raise ValueError(
            f"script {script_id} points outside ROM: 0x{ptr:08X} -> 0x{rom_offset:X}"
        )

    next_id = None
    next_ptr = None
    next_offset = None
    for candidate_id in range(1, entry_count):
        candidate_ptr = _read_u32(data, table_offset + candidate_id * 4)
        if candidate_ptr <= ptr:
            continue
        candidate_offset = gba_addr_to_rom_offset(candidate_ptr)
        if candidate_offset > rom_offset and candidate_offset <= len(data):
            if next_offset is None or candidate_offset < next_offset:
                next_id = candidate_id
                next_ptr = candidate_ptr
                next_offset = candidate_offset

    slot_size = None if next_offset is None else next_offset - rom_offset
    immediate_next_ptr = None
    immediate_next_offset = None
    if script_id + 1 <= script_count:
        immediate_next_ptr = _read_u32(data, table_offset + (script_id + 1) * 4)
        if immediate_next_ptr:
            immediate_next_offset = gba_addr_to_rom_offset(immediate_next_ptr)

    return {
        "script_id": script_id,
        "table_offset": table_offset,
        "pointer": ptr,
        "rom_offset": rom_offset,
        "next_script_id": next_id,
        "next_pointer": next_ptr,
        "next_rom_offset": next_offset,
        "slot_size": slot_size,
        "immediate_next_pointer": immediate_next_ptr,
        "immediate_next_rom_offset": immediate_next_offset,
        "immediate_next_is_slot_end": immediate_next_offset == next_offset,
    }


def _hex_or_none(value: int | bool | None) -> str:
    if isinstance(value, bool):
        return "yes" if value else "no"
    if value is None:
        return "unknown"
    return f"0x{value:X}"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("rom", type=Path, help="ROM image to inspect")
    parser.add_argument("--script-id", type=int, required=True)
    parser.add_argument("--table-offset", type=lambda value: int(value, 0), default=DEFAULT_TABLE_OFFSET)
    parser.add_argument("--script-count", type=int, default=DEFAULT_SCRIPT_COUNT)
    parser.add_argument("--json", action="store_true", help="print machine-readable JSON")
    args = parser.parse_args()

    slot = inspect_slot(args.rom, args.script_id, args.table_offset, args.script_count)
    if args.json:
        print(json.dumps(slot, indent=2, sort_keys=True))
        return 0

    print(f"script_id: {slot['script_id']}")
    print(f"table_offset: {_hex_or_none(slot['table_offset'])}")
    print(f"pointer: {_hex_or_none(slot['pointer'])}")
    print(f"rom_offset: {_hex_or_none(slot['rom_offset'])}")
    print(f"next_script_id: {slot['next_script_id']}")
    print(f"next_pointer: {_hex_or_none(slot['next_pointer'])}")
    print(f"next_rom_offset: {_hex_or_none(slot['next_rom_offset'])}")
    print(f"slot_size: {slot['slot_size']}")
    print(f"immediate_next_is_slot_end: {_hex_or_none(slot['immediate_next_is_slot_end'])}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
