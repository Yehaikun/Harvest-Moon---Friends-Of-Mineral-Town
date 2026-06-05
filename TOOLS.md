# FoMT Modding Tools

## Build
```bash
make clean && make -j2 fomt.gba   # Build ROM with all patches
make check-all                     # Verify integrity
```

## NPC Schedule
```bash
python3 tools/edit_npc_schedule.py fomt.gba --npc Karen     # View Karen's schedule
python3 tools/edit_npc_schedule.py fomt.gba --npc Mary --entry 0 --set 400 300 5  # Move Mary
```

## Text / Dialogue
```bash
python3 tools/extract_text.py fomt.gba --output texts/       # Extract all dialogue
python3 tools/patch_text.py fomt.gba --script 6 --list       # List dialogue strings
python3 tools/patch_text.py fomt.gba --script 6 --index 0 --update "Hello!\x05"
```

## Terrain / Collision
```bash
python3 tools/edit_terrain.py fomt.gba --map 2 --info        # Show terrain stats
python3 tools/edit_terrain.py fomt.gba --map 2 --export farm.txt  # Export terrain
python3 tools/edit_terrain.py fomt.gba --map 2 --set-rect 10 10 20 20 --value 0  # Make area walkable
```

## Tilemap
```bash
python3 tools/edit_tilemap.py fomt.gba --map 2 --info        # Show tilemap layers
python3 tools/edit_tilemap.py fomt.gba --map 63 --layer 1 --export tiles.csv
python3 tools/render_map.py fomt.gba --map 63                # Text preview
```

## Map Expansion
```bash
python3 tools/expand_any_map.py fomt.gba 2 --factor 2        # Farm 2x
python3 tools/create_new_map.py fomt.gba                     # Create new map (chicken coop)
```

## Entity / Internal
```bash
python3 tools/dump_entities.py fomt.gba                      # Entity handlers per map
python3 tools/list_npc_creators.py                            # 35 NPC creation functions
python3 tools/inspect_npcs.py fomt.gba                       # Raw schedule data
python3 tools/patch_entity_test.py fomt.gba                  # Map 63 → farm entities
```

## Scripts
```bash
python3 tools/relocate_script.py fomt.gba --script 167      # Free up script slot
scripts/script_167.mary                                       # Chicken coop warp logic
scripts/script_143.mary                                       # Return warp
```

## Current ROM Features
- 32MB (free space ~24MB)
- Farm 120×112 (2x)
- New mine map 80×60 (chicken coop entrance)
- North Town 352×176 (2x)
- South Town 260×96 (1.5x)
- 35 NPCs with mapped schedules
- 1134 scripts with dialogue
