#!/usr/bin/env python3
"""Decode simple 8-byte ROM tables shaped like {pointer, script_id}."""

from __future__ import annotations

import argparse
import csv
from pathlib import Path


GBA_ROM_BASE = 0x08000000


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    parser.add_argument("--offset", type=lambda value: int(value, 0), required=True)
    parser.add_argument("--size", type=lambda value: int(value, 0), required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    data = args.rom.read_bytes()
    rows = []
    for index, off in enumerate(range(args.offset, args.offset + args.size, 8)):
        if off + 8 > len(data):
            break
        ptr = int.from_bytes(data[off : off + 4], "little")
        script_id = int.from_bytes(data[off + 4 : off + 8], "little")
        ptr_offset = ptr - GBA_ROM_BASE if ptr >= GBA_ROM_BASE else ""
        rows.append(
            {
                "index": index,
                "rom_offset": f"0x{off:X}",
                "pointer": f"0x{ptr:08X}",
                "pointer_rom_offset": f"0x{ptr_offset:X}" if isinstance(ptr_offset, int) else "",
                "script_id": script_id,
            }
        )

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(
            handle,
            fieldnames=["index", "rom_offset", "pointer", "pointer_rom_offset", "script_id"],
            delimiter="\t",
        )
        writer.writeheader()
        writer.writerows(rows)

    print(f"wrote {len(rows)} entries to {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
