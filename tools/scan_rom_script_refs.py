#!/usr/bin/env python3
"""Scan pre-script ROM data for 32-bit script ID references."""

from __future__ import annotations

import argparse
import csv
import re
import struct
from pathlib import Path

from script_slot import DEFAULT_TABLE_OFFSET, DEFAULT_SCRIPT_COUNT, inspect_slot


INCBIN_RE = re.compile(
    r'\.incbin\s+"baserom\.gba"\s*,\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+|\d+)'
)
GLOBAL_RE = re.compile(r"\.global\s+([A-Za-z_][A-Za-z0-9_]*)")
LABEL_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*):")


def load_warp_script_ids(path: Path) -> list[int]:
    with path.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle, delimiter="\t")
        return sorted({int(row["script_id"]) for row in reader if row.get("script_id", "").isdigit()})


def min_script_offset(rom: Path, script_count: int, table_offset: int) -> int:
    offsets: list[int] = []
    for script_id in range(1, script_count + 1):
        try:
            slot = inspect_slot(rom, script_id, table_offset, script_count)
        except ValueError:
            continue
        rom_offset = slot.get("rom_offset")
        if isinstance(rom_offset, int):
            offsets.append(rom_offset)
    if not offsets:
        raise ValueError("could not find any script pointer offsets")
    return min(offsets)


def load_regions(paths: list[Path]) -> list[dict[str, int | str]]:
    regions: list[dict[str, int | str]] = []
    for path in paths:
        current_symbol = ""
        for raw in path.read_text(encoding="utf-8", errors="replace").splitlines():
            global_match = GLOBAL_RE.search(raw)
            if global_match:
                current_symbol = global_match.group(1)
            label_match = LABEL_RE.search(raw.strip())
            if label_match:
                current_symbol = label_match.group(1)
            incbin = INCBIN_RE.search(raw)
            if not incbin:
                continue
            start = int(incbin.group(1), 0)
            size = int(incbin.group(2), 0)
            regions.append(
                {
                    "start": start,
                    "end": start + size,
                    "symbol": current_symbol,
                    "source": str(path),
                }
            )
    return regions


def load_map_symbols(path: Path | None) -> list[dict[str, int | str]]:
    if path is None or not path.exists():
        return []

    symbols: list[dict[str, int | str]] = []
    for raw in path.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = raw.split()
        if len(parts) < 2 or not parts[0].startswith("0x080"):
            continue
        try:
            addr = int(parts[0], 16)
        except ValueError:
            continue
        name = parts[-1]
        if name.startswith(".") or "/" in name:
            continue
        symbols.append({"rom_offset": addr - 0x08000000, "symbol": name, "source": str(path)})

    symbols.sort(key=lambda row: int(row["rom_offset"]))
    return symbols


def find_region(
    regions: list[dict[str, int | str]],
    map_symbols: list[dict[str, int | str]],
    offset: int,
) -> tuple[str, str]:
    for region in regions:
        start = int(region["start"])
        end = int(region["end"])
        if start <= offset < end:
            return str(region["symbol"]), str(region["source"])
    best = None
    for symbol in map_symbols:
        symbol_offset = int(symbol["rom_offset"])
        if symbol_offset > offset:
            break
        best = symbol
    if best is not None:
        return str(best["symbol"]), str(best["source"])
    return "", ""


def scan_refs(
    rom_path: Path,
    script_ids: list[int],
    scan_end: int,
    regions: list[dict[str, int | str]],
    map_symbols: list[dict[str, int | str]],
) -> list[dict[str, str | int]]:
    data = rom_path.read_bytes()
    scan_end = min(scan_end, len(data))
    wanted = set(script_ids)
    rows: list[dict[str, str | int]] = []

    for offset in range(0, scan_end - 3, 4):
        value = struct.unpack_from("<I", data, offset)[0]
        if value not in wanted:
            continue
        symbol, source = find_region(regions, map_symbols, offset)
        context_start = max(0, offset - 16)
        context_end = min(len(data), offset + 20)
        context = data[context_start:context_end].hex(" ")
        rows.append(
            {
                "script_id": value,
                "rom_offset": f"0x{offset:X}",
                "region_symbol": symbol,
                "region_source": source,
                "context_hex": context,
            }
        )
    return rows


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    parser.add_argument("--warp-index", type=Path, default=Path("docs/generated/warp_index.tsv"))
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--table-offset", type=lambda value: int(value, 0), default=DEFAULT_TABLE_OFFSET)
    parser.add_argument("--script-count", type=int, default=DEFAULT_SCRIPT_COUNT)
    parser.add_argument("--scan-end", type=lambda value: int(value, 0))
    parser.add_argument("--data-asm", type=Path, nargs="*", default=list(Path("asm/data").glob("*.s")))
    parser.add_argument("--map-file", type=Path, default=Path("fomt.map"))
    args = parser.parse_args()

    script_ids = load_warp_script_ids(args.warp_index)
    scan_end = args.scan_end
    if scan_end is None:
        scan_end = min_script_offset(args.rom, args.script_count, args.table_offset)
    regions = load_regions(args.data_asm)
    map_symbols = load_map_symbols(args.map_file)
    rows = scan_refs(args.rom, script_ids, scan_end, regions, map_symbols)
    rows.sort(key=lambda row: (int(row["script_id"]), int(str(row["rom_offset"]), 0)))

    args.output.parent.mkdir(parents=True, exist_ok=True)
    fields = ["script_id", "rom_offset", "region_symbol", "region_source", "context_hex"]
    with args.output.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields, delimiter="\t")
        writer.writeheader()
        writer.writerows(rows)

    print(f"wrote {len(rows)} pre-script ROM refs to {args.output} (scan_end=0x{scan_end:X})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
