# Entity/Trigger System Research Notes

## Key Findings
- Entity function table at 0x080E602C: 66 entries (one per map)
- Each entry is a FUNCTION POINTER (in THUMB mode, odd addresses)
- Map 2 (farm): 0x080DC5A9 (has entities like chicken coop door)
- Maps 6-65: 0x08000639 (shared empty entity handler = no entities)
- Map 0-1, 3-4: 0x00000000 (no entities)
- Entity DATA format: unknown (embedded in init functions, not separate tables)

## What We Know
- Scripts are RIFF/SCR format with CODE + STR chunks
- Entity init functions create entity objects at specific positions
- Script ID 167 = chicken coop door on farm
- Entity position data format is encoded in the entity init function code

## Next Steps
- Decompile entity init functions to extract position data format
- Create entity data blocks for custom maps
- Build entity editor tool
- Implement map 63 return warp
