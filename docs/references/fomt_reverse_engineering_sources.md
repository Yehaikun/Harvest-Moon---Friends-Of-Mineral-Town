# FoMT Reverse Engineering Web Notes

This file keeps practical notes from external FoMT/GBA ROM hacking references.
It is not a mirror of the pages. Use it as a checklist for future decompilation,
script patching, map editing, text editing, and save/RAM debugging work.

## Source Index

| # | Source | URL | Current use |
|---|---|---|---|
| 1 | DataCrystal RAM Map | https://datacrystal.tcrf.net/wiki/Harvest_Moon:_Friends_of_Mineral_Town/RAM_map | Runtime state, save/RAM experiments, affection/time/money debugging |
| 2 | DataCrystal ROM Map | https://datacrystal.tcrf.net/wiki/Harvest_Moon:_Friends_of_Mineral_Town/ROM_map | TV program text/data ROM offsets |
| 3 | TCRF | https://tcrf.net/Harvest_Moon:_Friends_of_Mineral_Town | Unused/debug/region-difference lead; needs manual browser review because current fetch returns anti-bot page |
| 4 | khadim reverse-engineering thread | https://www.romhacking.net/forum/index.php?topic=28064.0 | Item/NPC/recipe/economy data lead; needs manual or archived review |
| 5 | Tile/compression thread | https://www.romhacking.net/forum/index.php?topic=21525.0 | MP tilemap and LZ77 compression lead; needs manual or archived review |
| 6 | StanHash/mary | https://github.com/StanHash/mary | Event script compiler/decompiler |
| 7 | HMMT Dumper/Inserter | https://www.romhacking.net/utilities/?author=6362&order=Game&page=utilities | Text extraction/insertion lead |
| 8 | khadim Google Sheets | https://drive.google.com/file/d/1HZco38hT4fXyiU4TR5_OD4m1zVAsSnV/view | Possibly stale spreadsheet lead; needs manual download/check |
| 9 | CodeBreaker code table | https://docshare.tips/harvest-moon_578d294ab6d87f4f2b8b4b3b.html | Cheat/RAM address cross-check lead; Wayback may be needed |
| 10 | GameFAQs guide | https://gamefaqs.gamespot.com/gba/589702-harvest-moon-friends-of-mineral-town/faqs/60141 | Gameplay behavior reference, festival/character schedule validation |
| 11 | Boktai tile map format | https://boktaihacking.net/w/index.php?title=Tile_map_file | GBA tilemap structure comparison lead |

## Confirmed Useful Facts

### Event scripts and mary

`mary` is the most important high-level tool for event script work. It can
compile custom script text into event bytecode and decompile existing event
bytecode back into readable script text.

Useful commands:

```sh
../stanhash_mary/target/release/mary decompile fomt.gba mary_scripts/lib_fomt.txt -o /tmp/script.mary --script-id 167
cpp -P scripts/script_167.mary | ../stanhash_mary/target/release/mary compile -o /tmp/script_167.bin --binary
make check-mary
```

Important table locations from mary:

| Game | Script pointer table address | ROM offset | Script IDs |
|---|---:|---:|---:|
| FoMT | `0x080F89D4` | `0x0F89D4` | `1..1328` |
| MFoMT | `0x081014BC` | `0x1014BC` | `1..1415` |

Known mary limits:

- FoMT exact-match decompile/recompile coverage is high, but not 100%.
- Broken FoMT decompilations listed by mary:
  - bugged lead assignment: `106, 143, 409, 410, 411, 532, 879`
  - incomplete switch logic: `356, 403, 540, 571, 610, 614, 617, 620, 623, 625, 629, 632, 635, 638, 640, 644, 647, 650, 653, 855, 858, 861, 1008, 1013, 1031`
- Scripts in those lists need extra verification before editing. This explains why some relationship/dialogue scripts can look partial or fail to recompile cleanly.

Current project state:

- `make check-mary` validates that the local mary binary and `mary_scripts/lib_fomt.txt` are available.
- The project still includes the script pointer table from `baserom.gba`:

```asm
gUnk_080F89D4:
    .incbin "baserom.gba", 0xF89D4, 0x14C4
```

- Therefore editing a `.mary` file alone does not yet rebuild the ROM script data.
- Until the script build pipeline is wired into the Makefile, ROM-changing script edits need either:
  - a tracked patch/insertion step, or
  - a manual local `baserom.gba` patch followed by `make fomt.gba`.

### Proven script patch workflow

The chicken-coop-to-beach test proved this workflow:

1. Identify script ID and current bytecode range from the pointer table.
2. Decompile script from the current ROM.
3. Edit the corresponding `scripts/script_N.mary`.
4. Compile it to binary with `mary compile --binary`.
5. Confirm the compiled byte length fits the original script slot.
6. Patch the local ROM data source.
7. Rebuild `fomt.gba`.
8. Decompile the rebuilt ROM script and verify the intended calls are present.
9. Test in emulator/hardware for white screen and in-game behavior.

Current tested example:

| Item | Value |
|---|---|
| Script | `scripts/script_167.mary` |
| Purpose | Entering the farm chicken coop sends the player to the beach |
| Original destination | `Proc016(17, 120, 208)` and `SetEntityPosition(0, 120, 208, 1)` |
| Tested destination | `Proc016(1, 24, 280)` and `SetEntityPosition(0, 24, 280, 3)` |
| Script ROM offset | `0x2CC48C` |
| Slot end | `0x2CC564` |
| Slot size | `216` bytes |
| Result | User tested in game and confirmed it works |

### Map and teleport clues

Current project names:

```cpp
MAP_BEACH = 0x001
MAP_FARM  = 0x002
```

Observed event-script behavior:

- `Proc016(map_id, x, y)` appears to load/switch the destination map.
- `SetEntityPosition(0, x, y, facing)` places player entity `0`.
- The tested beach coordinate `(24, 280, 3)` is safe enough for an entrance warp.

Practical use:

- To make a door/exit warp somewhere else, first find the script that handles that entrance.
- Prefer copying an existing known-safe destination triple from a vanilla boundary script.
- Avoid guessing collision coordinates until map collision data is understood.

### DataCrystal RAM map

The RAM map is useful for emulator watchpoints and cheat-code cross-checking.

Important notes:

- The page warns that many RAM addresses can have two stages:
  - Stage 1: never loaded from battery save.
  - Stage 2: loaded from battery save, using a `+0x2834` relocation.
- This means a RAM address that works in a fresh boot may be wrong after loading an in-game save.

Useful confirmed addresses:

| Runtime state | Stage 1 RAM address | Notes |
|---|---:|---|
| Farm name | `020025EC` | name storage uses 12 bytes |
| Farmer name | `020041B0` | player name |
| Weather | `020025E0` | current weather |
| Tomorrow weather | `020025E4` | next-day weather |
| Year | `020025E8` | date |
| Day | `020025E9` | date |
| Hour | `020025EA` | time |
| Minute | `020025EB` | time |
| Money | `02004080` | 4 bytes |
| Karen affection | `020044A4` | 2 bytes |
| Mary affection | `02004414` | 2 bytes |
| Popuri affection | `02004358` | 2 bytes |
| Elli affection | `020044D0` | 2 bytes |
| Ann affection | `02004524` | 2 bytes |
| Goddess affection | `020045A4` | 2 bytes |

Why this matters:

- Dialogue/event branches often depend on affection, date, flags, and time.
- Before changing a romance/event script, use emulator RAM watches to confirm the branch condition actually matches the player's save.
- This can prevent the common failure mode where a patched string exists but the game never reaches that branch.

### DataCrystal ROM map

The ROM map currently mainly lists TV program data offsets. Confirmed offsets:

| TV/program data | ROM offset |
|---|---:|
| Card Collector Chisato | `0x412F8C` |
| My Dear Princess | `0x418260` |
| Dueling Chefs | `0x421C21` |
| Fairy & Me | `0x424A08` |
| Fishing Hour | `0x43A1CC` |
| Races in the F-3.14 MGP | `0x43D1C0` |
| Goddess Rock-Paper-Scissors | `0x451940` |
| New Year's game shop | `0x4533C2` |
| Mechabot Ultror | `0x45406A` |
| Program Schedule | `0x45F181` |
| TV Shopping Network | `0x4B9D68` |
| Mine Research Group | `0x4C521C` |

Practical use:

- Use this when replacing TV text or finding TV-related scripts/data.
- Do not assume these are event-script IDs. Treat them as raw ROM data leads until mapped.

### GameFAQs guide

Use gameplay guides only as behavior references:

- schedule/event/festival timing checks
- tool behavior checks
- crop/animal/shop/festival expected behavior
- verifying whether a ROM change changed gameplay unintentionally

Do not use the guide as a technical map of the ROM.

## Leads That Need Follow-Up

### TCRF

Current automated fetch returned a generic anti-bot page, not the FoMT article.
Manual browser review is still useful for:

- unused items
- debug menu references
- regional differences
- hidden text/graphics that may map to unused ROM data

### romhacking.net threads

The two forum links should be reviewed manually or through the Internet Archive:

- khadim reverse engineering thread: likely useful for item IDs, prices, NPC data, recipes, and internal tables.
- tile/compression thread: likely useful for MP tilemap format and LZ77 compression work.

After reviewing, copy only derived offsets/structures/tool names into this project, not full forum posts.

### HMMT Dumper/Inserter

This is a FoMT text tool lead. Before using it in production:

1. Download and run it only in a disposable working copy.
2. Extract text from a clean ROM.
3. Reinsert text without changes.
4. Compare ROM output and test for text formatting bugs.
5. If it works, document supported text banks and limitations here.

### khadim Google Sheets and CodeBreaker table

Treat these as unverified leads. They can still help map RAM/ROM:

- Compare cheat addresses with DataCrystal RAM addresses.
- Convert CodeBreaker addresses to emulator watch addresses.
- Use only after testing in a known save state.

### Boktai tile map format

This is not FoMT-specific, but it may help reason about GBA-era tilemap layouts:

- tile indices
- palette/flip attributes
- compressed map chunks
- collision/attribute side tables

Only apply after confirming FoMT's actual map format from its own data.

## Next Engineering Tasks

1. Add a tracked `tools/patch_script.py` or Makefile rule that compiles selected `.mary` files and inserts them into a derived ROM image.
2. Stop relying on manual `baserom.gba` patching for script changes.
3. Build a script pointer-table inspector:

```sh
tool --script-id 167 --table-offset 0x0F89D4 --rom baserom.gba
```

It should print pointer, ROM offset, next pointer, slot size, and whether the compiled replacement fits.

4. Build a map warp index by scanning scripts for `Proc016(` and `SetEntityPosition(`.
5. Build a RAM-watch note file for emulator testing: date/time/weather/money/affection/event flags.
6. For text mods, test HMMT in a temporary branch before adopting it.

## Current Risk Notes

- Local `fomt.gba` can contain changes that are not reproducible from tracked source yet if `baserom.gba` was patched locally.
- `baserom.gba` should not be committed.
- `fomt-04.sgm` is a user save/state file. It can be committed only when explicitly requested.
- Script edits must be verified by rebuilding, decompiling the target script from the rebuilt ROM, and in-game testing.
