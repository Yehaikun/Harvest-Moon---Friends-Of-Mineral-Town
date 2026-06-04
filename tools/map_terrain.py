#!/usr/bin/env python3
"""Export MapData terrain_info and terrain_map for inspection."""

from __future__ import annotations

import argparse
import collections
import csv
import struct
from pathlib import Path


GBA_ROM_BASE = 0x08000000


def parse_int(value: str) -> int:
    return int(value, 0)


def ptr_to_offset(ptr: str) -> int | None:
    if not ptr:
        return None
    value = int(ptr, 0)
    if GBA_ROM_BASE <= value < GBA_ROM_BASE + 0x2000000:
        return value - GBA_ROM_BASE
    return None


def load_map_data(path: Path, map_id: int) -> dict[str, str]:
    with path.open("r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f, delimiter="\t")
        for row in reader:
            if int(row["map_id"]) == map_id:
                return row
    raise SystemExit(f"map_id {map_id} not found in {path}")


def terrain_symbol(value: int, solid: bool) -> str:
    if value == 0:
        return "."
    if solid:
        return "#"
    if value < 10:
        return str(value)
    return "?"


def export(args: argparse.Namespace) -> None:
    rom = args.rom.read_bytes()
    row = load_map_data(args.map_data, args.map_id)
    width = int(row["width"])
    height = int(row["height"])
    terrain_info_offset = ptr_to_offset(row["terrain_info"])
    terrain_map_offset = ptr_to_offset(row["terrain_map"])
    if terrain_info_offset is None or terrain_map_offset is None:
        raise SystemExit(f"map_id {args.map_id} has no ROM terrain pointers")

    terrain_map_size = width * height
    terrain_map = rom[terrain_map_offset : terrain_map_offset + terrain_map_size]
    if len(terrain_map) != terrain_map_size:
        raise SystemExit("terrain_map extends beyond ROM")

    max_index = max(terrain_map) if terrain_map else 0
    terrain_info = [
        struct.unpack_from("<I", rom, terrain_info_offset + i * 4)[0]
        for i in range(max_index + 1)
    ]

    name = row.get("map_symbol") or f"map_{args.map_id:03d}"
    stem = f"map_{args.map_id:03d}_{name.lower()}_terrain"
    args.out_dir.mkdir(parents=True, exist_ok=True)

    info_path = args.out_dir / f"{stem}_info.tsv"
    map_csv_path = args.out_dir / f"{stem}_map.csv"
    ascii_path = args.out_dir / f"{stem}_ascii.txt"
    summary_path = args.out_dir / f"{stem}_summary.tsv"

    with info_path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f, delimiter="\t")
        writer.writerow(["terrain_index", "raw", "solid_bit0", "script_or_action_candidate"])
        for index, raw in enumerate(terrain_info):
            writer.writerow([index, f"0x{raw:08X}", raw & 1, raw >> 17])

    with map_csv_path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        for y in range(height):
            start = y * width
            writer.writerow(terrain_map[start : start + width])

    ascii_lines = []
    for y in range(height):
        chars = []
        for x in range(width):
            value = terrain_map[y * width + x]
            raw = terrain_info[value] if value < len(terrain_info) else 1
            chars.append(terrain_symbol(value, bool(raw & 1)))
        ascii_lines.append("".join(chars))
    ascii_path.write_text("\n".join(ascii_lines) + "\n", encoding="utf-8")

    counts = collections.Counter(terrain_map)
    with summary_path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f, delimiter="\t")
        writer.writerow(
            [
                "map_id",
                "map_symbol",
                "width",
                "height",
                "terrain_info",
                "terrain_map",
                "unique_indices",
                "counts",
            ]
        )
        writer.writerow(
            [
                args.map_id,
                row.get("map_symbol", ""),
                width,
                height,
                row["terrain_info"],
                row["terrain_map"],
                len(counts),
                ",".join(f"{k}:{v}" for k, v in sorted(counts.items())),
            ]
        )

    print(f"wrote {info_path}")
    print(f"wrote {map_csv_path}")
    print(f"wrote {ascii_path}")
    print(f"wrote {summary_path}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)

    export_parser = sub.add_parser("export", help="export terrain data for one map")
    export_parser.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    export_parser.add_argument("--map-data", type=Path, default=Path("docs/generated/map_data_table.tsv"))
    export_parser.add_argument("--map-id", type=parse_int, required=True)
    export_parser.add_argument("--out-dir", type=Path, default=Path("docs/generated/terrain"))
    export_parser.set_defaults(func=export)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
