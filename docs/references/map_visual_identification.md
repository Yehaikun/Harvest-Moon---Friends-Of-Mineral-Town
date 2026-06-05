# FoMT Map Visual Identification

This document records visual identification results for rendered MapData maps.
It is intended to prevent future tilemap work from using misleading map names
or stale assumptions.

Source images:

- `map_previews/map_000.png` through `map_previews/map_065.png`
- `map_previews/atlas_all_maps.png`

## Critical Corrections

- `map_004` / `map_005` are North Town / northern town area.
- `map_006` / `map_007` are the player farm, not town maps.
- `map_006` is warm-season farm.
- `map_007` is winter farm.
- `map_002` / `map_003` are Rose Square festival / event plaza variants.
- Do not treat `map_004` / `map_005` as Rose Square. They are useful as
  building art sources, but they are North Town maps.
- Do not use project labels blindly. Verify by rendered preview and in-game
  entry route before placing new buildings.

## Outdoor Key Maps

| map_id | filename | width | height | identified location | type | confidence | notes |
|---:|---|---:|---:|---|---|---:|---|
| 0 | `map_000.png` | 128 | 88 | Player farm open field, normal season | outdoor | 98 | Pair with map 001. |
| 1 | `map_001.png` | 128 | 88 | Player farm open field, winter | outdoor | 98 | Pair with map 000. |
| 2 | `map_002.png` | 60 | 56 | Rose Square festival / event plaza, normal season | outdoor/event | 97 | Pair with map 003. |
| 3 | `map_003.png` | 60 | 56 | Rose Square festival / event plaza, winter | outdoor/event | 97 | Pair with map 002. |
| 4 | `map_004.png` | 176 | 88 | North Town, normal season | outdoor | 99 | Non-winter town building art source. |
| 5 | `map_005.png` | 176 | 88 | North Town, winter | outdoor | 99 | Winter counterpart of map 004. |
| 6 | `map_006.png` | 173 | 64 | Player farm, warm season | outdoor | 99 | Not Rose Square. |
| 7 | `map_007.png` | 173 | 64 | Player farm, winter | outdoor | 99 | Not Rose Square. |
| 8 | `map_008.png` | 64 | 80 | Mineral Town beach / pier, spring-summer | outdoor | 98 | Pair with map 009. |
| 9 | `map_009.png` | 64 | 80 | Mineral Town beach / pier | outdoor | 98 | Connected from Rose Square east path. |
| 10 | `map_010.png` | 64 | 48 | Mountain secret grove, normal season | outdoor | 98 | Pair with map 011. |
| 11 | `map_011.png` | 64 | 48 | Mountain secret grove, winter | outdoor | 98 | Pair with map 010. |
| 12 | `map_012.png` | 128 | 64 | Gotz carpenter yard, normal season | outdoor | 99 | Pair with map 013. |
| 13 | `map_013.png` | 128 | 64 | Gotz carpenter yard, winter | outdoor | 99 | Pair with map 012. |
| 14 | `map_014.png` | 150 | 100 | Mountain hot spring area, normal season | outdoor | 99 | Pair with map 015. |
| 15 | `map_015.png` | 150 | 100 | Mountain hot spring area, winter | outdoor | 99 | Pair with map 014. |
| 16 | `map_016.png` | 60 | 60 | Mother's Hill summit vista, winter | outdoor | 98 | Pair with map 017. |
| 17 | `map_017.png` | 60 | 60 | Mother's Hill summit vista, spring-summer | outdoor | 98 | Pair with map 016. |
| 62 | `map_062.png` | 30 | 20 | Beach / Zack house waterfront close-up | outdoor | 99 | Small outdoor transition map. |
| 63 | `map_063.png` | 30 | 20 | Beach west connector path | outdoor | 99 | Small outdoor transition map. |

## Indoor And Mine Maps

| map_id | filename | width | height | identified location | type | confidence |
|---:|---|---:|---:|---|---|---:|
| 18 | `map_018.png` | 30 | 28 | Zack house kitchen | indoor | 99 |
| 19 | `map_019.png` | 30 | 28 | Zack house living room | indoor | 99 |
| 20 | `map_020.png` | 30 | 28 | General store family bedroom | indoor | 98 |
| 21 | `map_021.png` | 30 | 28 | General store rear storage room | indoor | 98 |
| 22 | `map_022.png` | 46 | 42 | Inn first-floor dining room | indoor | 99 |
| 23 | `map_023.png` | 46 | 42 | Doctor's bedroom | indoor | 99 |
| 24 | `map_024.png` | 46 | 42 | Inn second-floor guest rooms | indoor | 99 |
| 25 | `map_025.png` | 36 | 42 | General store shop floor | indoor | 99 |
| 26 | `map_026.png` | 36 | 42 | Inn owner bedroom | indoor | 99 |
| 27 | `map_027.png` | 30 | 28 | Inn first-floor lobby | indoor | 99 |
| 28 | `map_028.png` | 30 | 28 | Inn kitchen / storage | indoor | 99 |
| 29 | `map_029.png` | 46 | 42 | Clinic treatment room | indoor | 99 |
| 30 | `map_030.png` | 46 | 42 | Church second-floor guest room | indoor | 99 |
| 31 | `map_031.png` | 46 | 42 | Church main hall | indoor | 99 |
| 32 | `map_032.png` | 30 | 28 | Church storage room | indoor | 99 |
| 33 | `map_033.png` | 30 | 28 | Church library | indoor | 99 |
| 34 | `map_034.png` | 30 | 28 | Church kitchen | indoor | 99 |
| 35 | `map_035.png` | 30 | 28 | Carter's bedroom | indoor | 99 |
| 36 | `map_036.png` | 30 | 28 | Chicken coop, small | indoor | 99 |
| 37 | `map_037.png` | 42 | 28 | Chicken coop, large | indoor | 99 |
| 38 | `map_038.png` | 46 | 36 | Animal barn, small | indoor | 99 |
| 39 | `map_039.png` | 76 | 36 | Animal barn, large | indoor | 99 |
| 40 | `map_040.png` | 30 | 28 | Animal barn fodder storage | indoor | 99 |
| 41 | `map_041.png` | 30 | 28 | Player house first expansion | indoor | 99 |
| 42 | `map_042.png` | 45 | 28 | Player house mid expansion variant | indoor | 99 |
| 43 | `map_043.png` | 59 | 28 | Player house full expansion living room | indoor | 99 |
| 44 | `map_044.png` | 30 | 28 | Orchard house first-floor kitchen | indoor | 99 |
| 45 | `map_045.png` | 30 | 28 | Orchard house second-floor bedroom | indoor | 99 |
| 46 | `map_046.png` | 30 | 28 | Gotz house first-floor dining/kitchen | indoor | 99 |
| 47 | `map_047.png` | 30 | 28 | Gotz house second-floor bedroom | indoor | 99 |
| 48 | `map_048.png` | 30 | 28 | Blacksmith workshop | indoor | 99 |
| 49 | `map_049.png` | 30 | 28 | Blacksmith kitchen / living room | indoor | 99 |
| 50 | `map_050.png` | 30 | 28 | Won / villa first-floor variant | indoor | 98 |
| 51 | `map_051.png` | 30 | 28 | Won / villa first-floor living room | indoor | 99 |
| 52 | `map_052.png` | 30 | 28 | Inn dormitory guest room | indoor | 99 |
| 53 | `map_053.png` | 30 | 28 | Fully upgraded player house, clock variant | indoor | 99 |
| 54 | `map_054.png` | 30 | 28 | Won / villa main bedroom | indoor | 99 |
| 55 | `map_055.png` | 30 | 28 | Fully upgraded player house, fireplace variant | indoor | 99 |
| 56 | `map_056.png` | 30 | 26 | Mine T-junction corridor | mine | 99 |
| 57 | `map_057.png` | 60 | 70 | Mine square hall | mine | 99 |
| 58 | `map_058.png` | 30 | 42 | Mine vertical corridor | mine | 99 |
| 59 | `map_059.png` | 30 | 26 | Mine horizontal corridor | mine | 99 |
| 60 | `map_060.png` | 30 | 20 | Small animal barn interior | indoor | 99 |
| 61 | `map_061.png` | 30 | 26 | Medium chicken coop interior | indoor | 99 |
| 64 | `map_064.png` | 30 | 20 | Mine short vertical entrance corridor | mine | 99 |
| 65 | `map_065.png` | 30 | 20 | Mine layered fork corridor | mine | 99 |

## Practical Rules For Future Tilemap Edits

1. Start from `baserom.gba` when creating a new visual patch unless explicitly
   layering on a known existing patch.
2. Render the target `map_id` before patching and inspect the PNG.
3. Patch both seasonal variants when editing an outdoor location:
   - Rose Square event/plaza variant: `map_002` and `map_003`
   - Farm: `map_006` and `map_007`, plus remember farm may have a special
     visual path in-game.
   - Beach: `map_008` and `map_009`
4. When adding a building to `map_002`, non-winter building art can be sourced
   from `map_004`; winter building art can be sourced from `map_005`. Because
   source maps do not have transparent building layers, tile-level reuse may
   bring source ground tiles around the building. For perfect integration, make
   a custom cutout / tile redraw rather than copying a rectangular tile region.
5. After patching, verify with:

   ```bash
   python3 tools/verify_tilemap_patch.py fomt.gba --map <id> --compare baserom.gba
   ```

6. If an edit does not appear in-game, first confirm the visible map ID by
   matching the screen against `map_previews/*.png`, not by relying on old
   symbol names.
