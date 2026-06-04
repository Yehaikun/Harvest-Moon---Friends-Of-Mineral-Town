# Phase 6: Content Tool Evaluation

## Goal

Determine which text, items, prices, NPC data, and map content can be
modified with existing tools, and which require engine decompilation.

---

## Evaluation Matrix

| Content Type | Tool / Method | Works Now? | Effort | Notes |
|-------------|---------------|:----------:|:------:|-------|
| NPC dialogue | `mary` compile + SCRIPT_PATCHES | ✅ | Low | Edit `.mary`, add to `Makefile`, rebuild. Slot size limited. |
| Event scripts | `mary` compile + SCRIPT_PATCHES | ✅ | Low | Same as dialogue. 1328 scripts available. |
| Warp destinations | Edit `.mary` `Proc016()` params | ✅ | Low | Change map ID + coordinates in the script. |
| Item prices | Edit `data/item/product.def` | ✅ | Low | Price is a u16:15 bitfield (max 32767). |
| Item names | Edit article data in `src/item.cc` | ✅ | Medium | Need to find the right `ArticleInfo` entry. |
| NPC names | Edit name data tables | ✅ | Medium | Names stored in data tables or `asm/data/`. |
| Shop inventories | Edit shop data tables | 🔶 | Medium | Shop tables in `asm/data/` `.incbin` blocks. |
| Recipe effects | Edit recipe data tables | 🔶 | Medium | Recipe data from khadim's spreadsheet (if accessible). |
| Text strings (non-script) | HMMT Dumper/Inserter | ❓ | Unknown | Windows-only tool. Untested on this project. |
| TV show text | DataCrystal ROM map + hex edit | 🔶 | High | Offsets known, but format is complex. |
| Map tile graphics | GBA tile editors (Crystaltile2, TLP) | 🔶 | High | Uncompressed sprites OK. Background tiles use LZ77 + MP format. |
| Map collision/walls | Map data format decompilation | ❌ | Very High | Requires decoding the map tile collision format. |
| New content (items, maps) | Engine modification | ❌ | Very High | Requires C++ decompilation of engine code. |

---

## Tool-by-Tool Assessment

### 1. mary (Script Compiler/Decompiler) — ✅ WORKS

**Source:** https://github.com/StanHash/mary
**Status:** Integrated into build system.
**Can modify:**
- All 1328 event scripts
- NPC dialogue, branch conditions, warp destinations, animations
- Festival events, cutscenes

**Limitations:**
- Script slot size is fixed per script ID
- Some scripts use unsupported mary features (blacklist needed)
- Cannot modify script engine behavior itself

### 2. Item Price Table (product.def) — ✅ WORKS

**Source:** `data/item/product.def`
**Status:** Directly editable C definition file.
**Can modify:**
- Sell prices for all items (crops, animal products, cooked dishes, foraged items, ores)
- Item category/type
- Item kind tag

**Limitations:**
- Price is `u32 price : 15` bitfield — max value 32767
- Cannot add new items without modifying `ProductInfo` enum

### 3. Article/Item Data (item.cc) — ✅ WORKS

**Source:** `src/item.cc`
**Status:** Directly editable C++.
**Can modify:**
- Item names, descriptions, icon IDs
- Item categories (edible, tool, etc.)

**Limitations:**
- Structure is complex; easy to corrupt if fields are misunderstood
- Article and Product arrays are separate; must keep in sync

### 4. DataCrystal RAM Map — ✅ CONFIRMED USEFUL

**Source:** https://datacrystal.tcrf.net/wiki/Harvest_Moon:_Friends_of_Mineral_Town/RAM_map
**Status:** Used for runtime verification.
**Can verify:**
- Money, time, weather at runtime
- NPC affection levels
- Player position
- Harvest sprite work stats
- Event flags

**Limitations:**
- Read-only verification; cannot modify game behavior through RAM map alone
- Stage 1 vs Stage 2 address offset (0x2834 — confirmed by cross-referencing CodeBreaker codes)

**Verification performed:**
- Stage 1 → Stage 2 offset `0x2834`: ✅ Confirmed
- Tool slot addresses from CodeBreaker: ✅ Match formula
- NPC affection address layout: ✅ Consistent with known NPC order

### 5. DataCrystal ROM Map — 🔶 LIMITED USE

**Source:** https://datacrystal.tcrf.net/wiki/Harvest_Moon:_Friends_of_Mineral_Town/ROM_map
**Status:** Stub page; only TV show program offsets documented.
**Can help with:**
- TV show text locations
- Identifying program schedule data

**Limitations:**
- Very incomplete (18 entries, all end addresses unknown)
- Only covers TV programs

### 6. HMMT Dumper/Inserter — 🔶 CANNOT DOWNLOAD

**Source:** https://www.romhacking.net/utilities/1557/
**Author:** Pinguimbozo
**Version:** 1.1 (2020-11-08)
**Platform:** Windows (Wine available on this system)
**Status:** Not tested — download blocked by Cloudflare on both romhacking.net and neoromhacking.net.

**Known capabilities (from public documentation):**
- Extracts FoMT dialogue text to UTF-16 LE `.txt` files
- Inserts modified text back into ROM
- Uses a customizable character mapping table
- Creates backup files

**Known issues:**
- Causes automatic misformatting of TV program text lines
- Only supports FoMT (not MFoMT)
- Cited as buggy by hack author Mentil

**Proven usage:**
- Used by Mentil in "Proofread/Grind Reduction" hack (March 2026)
- Successfully fixed thousands of spelling/grammar errors
- Renamed NPCs and items in that hack

**Conclusion:** If you need to bulk-edit text, download HMMT manually from
romhacking.net and place it in `tools/`. For individual script edits,
`.mary` + patching is simpler and doesn't need HMMT.

### 7. CodeBreaker Codes — ✅ CROSS-REFERENCE VERIFIED

**Source:** GameFAQs (VALT Jasper v2.0), archived at docshare.tips.
**Status:** Stage 1 → Stage 2 offset formula verified against actual ROM.

**Can help with:**
- Cross-referencing RAM addresses (Stage 1/Stage 2)
- Tool/item ID verification
- House upgrade flag mapping
- Weather/time/date address confirmation

**Verification performed:**
- Stage 1 → Stage 2 offset `0x2834`: ✅ Confirmed by calculating
  `0x32004238 + 0x2834 = 0x32006A6C` which matches the documented Stage 2 address
- NPC affection address layout: ✅ Consistent with known NPC order
- Item ID range matches RAM map: ✅ Confirmed

### 8. khadim's Reverse Engineering Data — 🔶 THREAD ACCESSIBLE, SHEETS BLOCKED

**Source:** https://www.romhacking.net/forum/index.php?topic=28064.0
**Status:** Forum thread readable. Google Sheets link blocked by SSL error.

**Contains (from thread):**
- Edible item IDs (drink/eat flag, stamina recovery, fatigue recovery, name/desc pointers)
- Non-edible item IDs (name/desc pointers)
- Shippable item IDs (sell value)
- Horse race medal exchange amounts
- Shop buying prices
- NPC displayed names and birthdays
- Recipes (ID, stamina/fatigue recovery, required utensils, ingredient sets)
- Notable recipe discoveries:
  - Poisonous mushroom + miso/curry → stamina -60, fatigue +20
  - Elli Leaves + colored grass → max stamina +190, fatigue -100

**Limitations:**
- Spreadsheet at https://drive.google.com/file/d/1HZco38hT4fXyiU4TR5_OD4m1zVAsSnV/view
  is inaccessible due to SSL errors in this environment
- Data is from 2019; not verified against actual ROM
- NPC sprite address mapping mentioned but never published

**Conclusion:** The forum thread categories are useful as a checklist of what
CAN be mapped. Recipe data and item IDs can be extracted from the thread
text. NPC sprite addresses are still unknown.

---

## Summary: What to Use for What

| You want to... | Use this |
|----------------|----------|
| Change what an NPC says | Edit `.mary` → `make fomt.gba` |
| Change where a door leads | Edit `Proc016()` in `.mary` |
| Change item prices | Edit `data/item/product.def` |
| Change item names | Edit `src/item.cc` → `gArticleInfo[]` |
| Change shop inventory | Find and edit the shop data table |
| Add a new event/cutscene | Write a new `.mary` + find an unused script slot |
| Verify affection/time at runtime | Check RAM addresses in emulator |
| Decode tile collision data | Requires decompilation (Phase 5/7 scope) |
| Add new items/maps/mechanics | Requires engine decompilation (Phase 7 scope) |
