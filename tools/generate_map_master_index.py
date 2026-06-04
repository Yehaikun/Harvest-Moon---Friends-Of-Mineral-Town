#!/usr/bin/env python3
"""Generate a map-centric index from the current script warp index.

This file is intentionally conservative: fields that are not fully verified are
named as candidates instead of facts. The goal is to create a stable map ID
index that can be extended as visual tilemaps, collision data, and entity tables
are decoded.
"""

from __future__ import annotations

import argparse
import csv
import re
from collections import defaultdict
from pathlib import Path


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


def int_or_none(value: str) -> int | None:
    if value == "":
        return None
    return int(value, 0)


def minmax(values: list[int]) -> str:
    if not values:
        return ""
    return f"{min(values)}..{max(values)}"


def load_map_data(path: Path) -> dict[int, dict[str, str]]:
    if not path.exists():
        return {}

    rows: dict[int, dict[str, str]] = {}
    with path.open("r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f, delimiter="\t")
        for row in reader:
            if row.get("map_id", ""):
                rows[int(row["map_id"])] = row
    return rows


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--warp-index", default="docs/generated/warp_index.tsv")
    parser.add_argument("--map-data", default="docs/generated/map_data_table.tsv")
    parser.add_argument("--entities", default="include/decomp/entities.hh")
    parser.add_argument("--output", default="docs/generated/map_master_index.tsv")
    args = parser.parse_args()

    warp_index = Path(args.warp_index)
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)

    known_maps = parse_entities(Path(args.entities))
    map_data = load_map_data(Path(args.map_data))
    rows_by_map: dict[int, list[dict[str, str]]] = defaultdict(list)

    with warp_index.open("r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f, delimiter="\t")
        for row in reader:
            map_id = int_or_none(row.get("map_id", ""))
            if map_id is None:
                continue
            rows_by_map[map_id].append(row)

    all_map_ids = sorted(set(known_maps) | set(rows_by_map) | set(map_data))
    out_rows: list[dict[str, str]] = []

    for map_id in all_map_ids:
        warp_rows = rows_by_map.get(map_id, [])
        data_row = map_data.get(map_id, {})
        script_ids = sorted({int(r["script_id"]) for r in warp_rows if r.get("script_id")})
        proc_x = [int(r["proc_x"]) for r in warp_rows if r.get("proc_x")]
        proc_y = [int(r["proc_y"]) for r in warp_rows if r.get("proc_y")]
        entity_x = [int(r["entity_x"]) for r in warp_rows if r.get("entity_x")]
        entity_y = [int(r["entity_y"]) for r in warp_rows if r.get("entity_y")]
        safe_points = []

        for r in warp_rows[:8]:
            if r.get("has_player_position") == "yes":
                safe_points.append(
                    f"s{r['script_id']}({r['entity_x']},{r['entity_y']},f{r['facing']})"
                )

        # Existing docs identify a compact 0x80-byte map-indexed region here.
        # It is not yet proven to be the full 64x64 collision grid, so keep it
        # marked as a candidate until the format is verified in-game.
        collision_candidate = ""
        if 0 <= map_id <= 0x3A:
            collision_candidate = f"0x{0x120BBC + map_id * 0x80:X}"

        out_rows.append(
            {
                "map_id": str(map_id),
                "map_id_hex": f"0x{map_id:03X}",
                "map_symbol": known_maps.get(map_id, ""),
                "map_name_cn": KNOWN_CHINESE_NAMES.get(map_id, ""),
                "warp_count": str(len(warp_rows)),
                "warp_scripts": ",".join(str(s) for s in script_ids[:24]),
                "proc_x_range": minmax(proc_x),
                "proc_y_range": minmax(proc_y),
                "entity_x_range": minmax(entity_x),
                "entity_y_range": minmax(entity_y),
                "known_safe_spawn_points": ";".join(safe_points),
                "collision_candidate_offset": collision_candidate,
                "collision_candidate_size": "0x80" if collision_candidate else "",
                "map_data_entry": data_row.get("entry_rom_offset", ""),
                "map_width": data_row.get("width", ""),
                "map_height": data_row.get("height", ""),
                "is_interior": data_row.get("is_interior", ""),
                "terrain_info": data_row.get("terrain_info", ""),
                "terrain_map": data_row.get("terrain_map", ""),
                "visual_tilemap_candidate": data_row.get("packed_img", ""),
                "entity_table_candidate": "",
                "notes": (
                    "MapData decoded from GetMapData table; collision candidate is not yet "
                    "the verified full movement grid"
                ),
            }
        )

    fieldnames = [
        "map_id",
        "map_id_hex",
        "map_symbol",
        "map_name_cn",
        "warp_count",
        "warp_scripts",
        "proc_x_range",
        "proc_y_range",
        "entity_x_range",
        "entity_y_range",
        "known_safe_spawn_points",
        "collision_candidate_offset",
        "collision_candidate_size",
        "map_data_entry",
        "map_width",
        "map_height",
        "is_interior",
        "terrain_info",
        "terrain_map",
        "visual_tilemap_candidate",
        "entity_table_candidate",
        "notes",
    ]

    with output.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t")
        writer.writeheader()
        writer.writerows(out_rows)

    print(f"wrote {output} ({len(out_rows)} maps)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
