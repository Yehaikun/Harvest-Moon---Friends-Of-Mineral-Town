#!/usr/bin/env python3
"""Decode the MapData table reached by GetMapData(map_id)."""

from __future__ import annotations

import argparse
import csv
import re
import struct
from pathlib import Path


DEFAULT_OFFSET = 0x105EDC
DEFAULT_SIZE = 0xA50
ENTRY_SIZE = 0x28
GBA_ROM_BASE = 0x08000000

KNOWN_CHINESE_NAMES = {
    0x000: "母亲之山",
    0x001: "海滩",
    0x002: "农场",
    0x003: "森林",
    0x004: "教堂后院",
    0x005: "矿物镇北",
    0x006: "玫瑰广场",
    0x007: "矿物镇南",
    0x008: "母亲之山顶",
    0x00F: "商店室内",
    0x01D: "玩家房屋",
    0x03A: "泉水矿洞",
}

POINTER_FIELDS = [
    "packed_img",
    "packed_pal1",
    "packed_pal2",
    "packed_tiles1",
    "packed_tiles2",
    "packed_tiles3",
    "terrain_info",
    "terrain_map",
]


def parse_int(value: str) -> int:
    return int(value, 0)


def parse_entities(path: Path) -> dict[int, str]:
    maps: dict[int, str] = {}
    pattern = re.compile(r"\b(MAP_[A-Z0-9_]+)\s*=\s*(0x[0-9A-Fa-f]+|\d+)")

    if not path.exists():
        return maps

    for line in path.read_text(encoding="utf-8").splitlines():
        match = pattern.search(line)
        if match:
            maps[int(match.group(2), 0)] = match.group(1)

    return maps


def fmt_ptr(value: int) -> str:
    return "" if value == 0 else f"0x{value:08X}"


def ptr_to_rom_offset(value: int) -> str:
    if GBA_ROM_BASE <= value < GBA_ROM_BASE + 0x2000000:
        return f"0x{value - GBA_ROM_BASE:X}"
    return ""


def decode(args: argparse.Namespace) -> None:
    rom = args.rom.read_bytes()
    known_maps = parse_entities(args.entities)
    count = args.size // ENTRY_SIZE
    rows: list[dict[str, str]] = []

    for map_id in range(count):
        offset = args.offset + map_id * ENTRY_SIZE
        entry = rom[offset : offset + ENTRY_SIZE]
        if len(entry) != ENTRY_SIZE:
            raise SystemExit(f"short MapData entry at 0x{offset:X}")

        ptrs = struct.unpack_from("<8I", entry, 0)
        width, height = struct.unpack_from("<HH", entry, 0x20)
        is_interior = entry[0x24]

        row = {
            "map_id": str(map_id),
            "map_id_hex": f"0x{map_id:03X}",
            "map_symbol": known_maps.get(map_id, ""),
            "map_name_cn": KNOWN_CHINESE_NAMES.get(map_id, ""),
            "entry_rom_offset": f"0x{offset:X}",
            "width": str(width),
            "height": str(height),
            "is_interior": str(is_interior),
        }
        for field, value in zip(POINTER_FIELDS, ptrs):
            row[field] = fmt_ptr(value)
            row[f"{field}_rom_offset"] = ptr_to_rom_offset(value)
        rows.append(row)

    fieldnames = [
        "map_id",
        "map_id_hex",
        "map_symbol",
        "map_name_cn",
        "entry_rom_offset",
        *POINTER_FIELDS,
        *(f"{field}_rom_offset" for field in POINTER_FIELDS),
        "width",
        "height",
        "is_interior",
    ]

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t")
        writer.writeheader()
        writer.writerows(rows)

    print(f"wrote {args.output} ({len(rows)} MapData entries)")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    parser.add_argument("--entities", type=Path, default=Path("include/decomp/entities.hh"))
    parser.add_argument("--offset", type=parse_int, default=DEFAULT_OFFSET)
    parser.add_argument("--size", type=parse_int, default=DEFAULT_SIZE)
    parser.add_argument("--output", type=Path, default=Path("docs/generated/map_data_table.tsv"))
    decode(parser.parse_args())


if __name__ == "__main__":
    main()
