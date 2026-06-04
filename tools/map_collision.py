#!/usr/bin/env python3
"""Read-only helpers for map collision/boundary research.

The 0x120BBC + map_id * 0x80 records are useful map-indexed candidates, but
they are not yet proven to be the full 64x64 collision grids. This tool keeps
that distinction explicit.
"""

from __future__ import annotations

import argparse
import collections
import sys
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
SCRIPT_TOOLS = REPO_ROOT / "tools" / "scripts"
sys.path.insert(0, str(SCRIPT_TOOLS))

from decompress import UnpackException, unpack  # noqa: E402


COLLISION_CANDIDATE_BASE = 0x120BBC
COLLISION_CANDIDATE_STRIDE = 0x80
COLLISION_CANDIDATE_SIZE = 0x80

KNOWN_MAP_NAMES = {
    0x000: "mothers_hill",
    0x001: "beach",
    0x002: "farm",
    0x003: "forest",
    0x004: "church_rear",
    0x005: "north_town",
    0x006: "rose_square",
    0x007: "south_town",
    0x008: "mothers_peak",
    0x00F: "shop_interior",
    0x01D: "player_house",
    0x03A: "spring_mine",
}


def parse_int(value: str) -> int:
    return int(value, 0)


def read_rom(path: Path) -> bytes:
    data = path.read_bytes()
    if len(data) < 0x100000:
        raise SystemExit(f"ROM too small: {path} ({len(data)} bytes)")
    return data


def candidate_offset(map_id: int) -> int:
    return COLLISION_CANDIDATE_BASE + map_id * COLLISION_CANDIDATE_STRIDE


def hex_dump(data: bytes, base: int) -> str:
    lines = []
    for row in range(0, len(data), 16):
        chunk = data[row : row + 16]
        hex_part = " ".join(f"{b:02X}" for b in chunk)
        ascii_part = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
        lines.append(f"{base + row:08X}  {hex_part:<47}  |{ascii_part}|")
    return "\n".join(lines) + "\n"


def export_candidate(args: argparse.Namespace) -> None:
    rom = read_rom(args.rom)
    map_id = args.map_id
    offset = candidate_offset(map_id)
    end = offset + COLLISION_CANDIDATE_SIZE
    if end > len(rom):
        raise SystemExit(f"candidate record outside ROM: 0x{offset:X}..0x{end:X}")

    data = rom[offset:end]
    args.out_dir.mkdir(parents=True, exist_ok=True)

    name = KNOWN_MAP_NAMES.get(map_id, f"map_{map_id:03d}")
    stem = f"map_{map_id:03d}_{name}_candidate"
    bin_path = args.out_dir / f"{stem}.bin"
    hex_path = args.out_dir / f"{stem}.hex.txt"
    summary_path = args.out_dir / f"{stem}.summary.tsv"

    bin_path.write_bytes(data)
    hex_path.write_text(hex_dump(data, offset), encoding="utf-8")

    counts = collections.Counter(data)
    top_counts = ",".join(f"0x{k:02X}:{v}" for k, v in counts.most_common(12))
    summary = [
        "map_id\tmap_name\toffset\tsize\tunique_values\ttop_counts\tnote",
        (
            f"{map_id}\t{name}\t0x{offset:X}\t0x{len(data):X}\t"
            f"{len(counts)}\t{top_counts}\t"
            "candidate 0x80-byte map-indexed record; not verified full 64x64 collision grid"
        ),
    ]
    summary_path.write_text("\n".join(summary) + "\n", encoding="utf-8")

    print(f"wrote {bin_path}")
    print(f"wrote {hex_path}")
    print(f"wrote {summary_path}")


def scan_popuri(args: argparse.Namespace) -> None:
    rom = read_rom(args.rom)
    start = max(0, args.start)
    end = min(len(rom), args.end)
    sizes = set(args.sizes)
    rows = ["offset\tdecoded_size\tformat\tladder_spec"]

    for offset in range(start, end, args.step):
        if rom[offset] != 0x70:
            continue
        try:
            decoded, fmt_spec, ladder_spec = unpack(rom, offset)
        except (UnpackException, IndexError):
            continue
        if len(decoded) in sizes:
            rows.append(f"0x{offset:X}\t{len(decoded)}\t{fmt_spec}\t{ladder_spec}")

    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text("\n".join(rows) + "\n", encoding="utf-8")
        print(f"wrote {args.output} ({len(rows) - 1} matches)")
    else:
        print("\n".join(rows))


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)

    export = sub.add_parser("export-candidate", help="export one 0x80-byte map candidate record")
    export.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    export.add_argument("--map-id", type=parse_int, required=True)
    export.add_argument("--out-dir", type=Path, default=Path("docs/generated/collision"))
    export.set_defaults(func=export_candidate)

    scan = sub.add_parser("scan-popuri", help="scan ROM for popuri-compressed blocks")
    scan.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    scan.add_argument("--start", type=parse_int, default=0)
    scan.add_argument("--end", type=parse_int, default=0x800000)
    scan.add_argument("--step", type=parse_int, default=4)
    scan.add_argument("--sizes", type=lambda s: [parse_int(x) for x in s.split(",")], default=[4096, 4112])
    scan.add_argument("--output", type=Path)
    scan.set_defaults(func=scan_popuri)

    return parser


def main() -> None:
    parser = build_parser()
    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
