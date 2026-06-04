#!/usr/bin/env python3
"""Scan mary scripts for map warp calls."""

from __future__ import annotations

import argparse
import csv
import re
from pathlib import Path


SCRIPT_RE = re.compile(r"script_(\d+)\.mary$")
PROC016_RE = re.compile(r"\bProc016\(\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*\)")
SET_ENTITY_RE = re.compile(
    r"\bSetEntityPosition\(\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*\)"
)
MAP_ENUM_RE = re.compile(r"\b(MAP_[A-Z0-9_]+)\s*=\s*(0x[0-9A-Fa-f]+|\d+)")


def load_map_names(header: Path | None) -> dict[int, str]:
    if header is None or not header.exists():
        return {}

    names: dict[int, str] = {}
    for line in header.read_text(encoding="utf-8", errors="replace").splitlines():
        match = MAP_ENUM_RE.search(line)
        if not match:
            continue
        names[int(match.group(2), 0)] = match.group(1)
    return names


def script_id_from_path(path: Path) -> int:
    match = SCRIPT_RE.search(path.name)
    if not match:
        raise ValueError(f"not a script_N.mary path: {path}")
    return int(match.group(1))


def scan_script(path: Path, map_names: dict[int, str]) -> list[dict[str, str | int]]:
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    records: list[dict[str, str | int]] = []
    script_id = script_id_from_path(path)

    for index, line in enumerate(lines):
        proc = PROC016_RE.search(line)
        if not proc:
            continue

        map_id = int(proc.group(1))
        proc_x = int(proc.group(2))
        proc_y = int(proc.group(3))
        player_position = None
        next_entity_position = None

        for follow_index in range(index + 1, min(index + 13, len(lines))):
            entity = SET_ENTITY_RE.search(lines[follow_index])
            if not entity:
                continue
            entity_id = int(entity.group(1))
            position = {
                "line": follow_index + 1,
                "entity_id": entity_id,
                "entity_x": int(entity.group(2)),
                "entity_y": int(entity.group(3)),
                "facing": int(entity.group(4)),
            }
            if next_entity_position is None:
                next_entity_position = position
            if entity_id == 0:
                player_position = position
                break

        chosen = player_position or next_entity_position or {}
        records.append(
            {
                "script_id": script_id,
                "script": path.name,
                "line": index + 1,
                "map_id": map_id,
                "map_name": map_names.get(map_id, ""),
                "proc_x": proc_x,
                "proc_y": proc_y,
                "player_line": chosen.get("line", ""),
                "entity_id": chosen.get("entity_id", ""),
                "entity_x": chosen.get("entity_x", ""),
                "entity_y": chosen.get("entity_y", ""),
                "facing": chosen.get("facing", ""),
                "has_player_position": "yes" if player_position else "no",
                "source": str(path),
            }
        )

    return records


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--scripts-dir", type=Path, default=Path("scripts"))
    parser.add_argument("--map-header", type=Path, default=Path("include/decomp/entities.hh"))
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    map_names = load_map_names(args.map_header)
    records: list[dict[str, str | int]] = []
    for path in sorted(args.scripts_dir.glob("script_*.mary"), key=script_id_from_path):
        records.extend(scan_script(path, map_names))

    args.output.parent.mkdir(parents=True, exist_ok=True)
    fields = [
        "script_id",
        "script",
        "line",
        "map_id",
        "map_name",
        "proc_x",
        "proc_y",
        "player_line",
        "entity_id",
        "entity_x",
        "entity_y",
        "facing",
        "has_player_position",
        "source",
    ]
    with args.output.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields, delimiter="\t")
        writer.writeheader()
        writer.writerows(records)

    print(f"wrote {len(records)} warp records to {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
