#!/usr/bin/env python3
"""Build candidate cross references between mary scripts."""

from __future__ import annotations

import argparse
import csv
import re
from pathlib import Path


SCRIPT_RE = re.compile(r"script_(\d+)\.mary$")
CALL_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\(([^\"()]*)\)")
INT_RE = re.compile(r"^-?\d+$")


LOW_CONFIDENCE_CALLS = {
    # These often refer to flags, item IDs, music IDs, or entity IDs instead of
    # script IDs. Keep them in the index, but label them conservatively.
    "Func03E",
    "Proc03F",
    "PlaySong",
    "SetEntityPosition",
    "Proc016",
    "Case",
    "SwitchId",
    "Val",
    "JumpId",
    "Label",
    "Beq",
    "Bne",
    "Goto",
}


def script_id_from_path(path: Path) -> int:
    match = SCRIPT_RE.search(path.name)
    if not match:
        raise ValueError(f"not a script_N.mary path: {path}")
    return int(match.group(1))


def load_warp_script_ids(path: Path | None) -> set[int]:
    if path is None or not path.exists():
        return set()
    with path.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle, delimiter="\t")
        return {int(row["script_id"]) for row in reader if row.get("script_id", "").isdigit()}


def confidence_for(callee: str, referenced_id: int, warp_ids: set[int]) -> str:
    if referenced_id not in warp_ids:
        return "low"
    if callee in LOW_CONFIDENCE_CALLS:
        return "low"
    if callee.startswith("Proc") or callee.startswith("Func"):
        return "medium"
    return "medium"


def scan_script(path: Path, all_script_ids: set[int], warp_ids: set[int]) -> list[dict[str, str | int]]:
    source_script_id = script_id_from_path(path)
    records: list[dict[str, str | int]] = []
    for line_no, line in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), start=1):
        stripped = line.strip()
        if not stripped or stripped.startswith("//") or stripped.startswith("const MESSAGE"):
            continue
        for call in CALL_RE.finditer(line):
            callee = call.group(1)
            args = [arg.strip() for arg in call.group(2).split(",")]
            for arg_index, arg in enumerate(args, start=1):
                if not INT_RE.match(arg):
                    continue
                referenced_id = int(arg)
                if referenced_id not in all_script_ids:
                    continue
                records.append(
                    {
                        "referenced_script_id": referenced_id,
                        "referenced_has_warp": "yes" if referenced_id in warp_ids else "no",
                        "source_script_id": source_script_id,
                        "source_script": path.name,
                        "line": line_no,
                        "callee": callee,
                        "arg_index": arg_index,
                        "confidence": confidence_for(callee, referenced_id, warp_ids),
                        "is_self_reference": "yes" if referenced_id == source_script_id else "no",
                        "context": stripped,
                    }
                )
    return records


def write_tsv(path: Path, rows: list[dict[str, str | int]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fields = [
        "referenced_script_id",
        "referenced_has_warp",
        "source_script_id",
        "source_script",
        "line",
        "callee",
        "arg_index",
        "confidence",
        "is_self_reference",
        "context",
    ]
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields, delimiter="\t")
        writer.writeheader()
        writer.writerows(rows)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--scripts-dir", type=Path, default=Path("scripts"))
    parser.add_argument("--warp-index", type=Path, default=Path("docs/generated/warp_index.tsv"))
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--warp-output", type=Path)
    args = parser.parse_args()

    script_paths = sorted(args.scripts_dir.glob("script_*.mary"), key=script_id_from_path)
    all_script_ids = {script_id_from_path(path) for path in script_paths}
    warp_ids = load_warp_script_ids(args.warp_index)
    rows: list[dict[str, str | int]] = []
    for path in script_paths:
        rows.extend(scan_script(path, all_script_ids, warp_ids))

    rows.sort(
        key=lambda row: (
            int(row["referenced_script_id"]),
            int(row["source_script_id"]),
            int(row["line"]),
            str(row["callee"]),
        )
    )
    write_tsv(args.output, rows)

    if args.warp_output is not None:
        warp_rows = [
            row
            for row in rows
            if row["referenced_has_warp"] == "yes"
            and row["is_self_reference"] == "no"
            and row["confidence"] != "low"
        ]
        write_tsv(args.warp_output, warp_rows)
        print(f"wrote {len(warp_rows)} warp candidate xrefs to {args.warp_output}")

    print(f"wrote {len(rows)} script xrefs to {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
