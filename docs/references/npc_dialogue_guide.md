# Phase 3: NPC Dialogue & Event Modification Guide

## Goal

Be able to locate and modify any NPC's dialogue, understand the branch
conditions that control which dialogue is shown, and verify changes work
in-game using known RAM addresses.

---

## 1. NPC Dialogue Script Overview

### Script ID Ranges

| Script IDs | Purpose | How to modify |
|------------|---------|---------------|
| `1`–`~999` | Game events (cutscenes, festivals, animal interactions) | mary scripts |
| `1000`–`~1030` | NPC first-introduction / meeting scripts (large, 5-33KB) | mary scripts |
| `1040`–`~1060` | Festival dialogue (horse race, cooking festival, etc.) | mary scripts |
| `1100`–`1328` | Various event/schedule text (small, 200-700 bytes) | Mostly HMMT territory |
| NPC daily dialogue | General interaction text | **HMMT** (extracted to `tools/HMMT/HMMT_v1.1/SCRIPTS/`) |

### Script File Location

All event scripts are in `scripts/script_N.mary`. Each file contains exactly
one script block:

```c
script 167 EventScript_167
{
    const MESSAGE_0 = "You can't go inside\r\nwhile riding a horse!\x05"
    if GetEntityFacing(0) == 1
    {
        // ... conditions and actions ...
    }
}
```

### Dialogue Text Encoding

- `const MESSAGE_N = "..."` — defines a text string
- `\r\n` — newline inside a single message box
- `\x05` — end of message box (advance to next box or close)
- `\x0C` — continue to next message box (wait for player input)
- `\xFF!` — inserts the player's name
- `\xFF%` — inserts an animal/NPC name
- `\xFF&` — inserts a number
- `TalkOpen()` — opens the dialogue window
- `TalkMessage(MESSAGE_N)` — displays a message
- `TalkClose()` — closes the dialogue window

### Speaker Control

The current speaker/portrait is set by `Proc030(SpeakerID)`:

```c
Proc030(121)  // show Mary's portrait
TalkOpen()
TalkMessage(MESSAGE_0)
TalkClose()
```

#### Known Speaker IDs (Proc030 mapping)

| Proc030 | Character | Notes |
|---------|-----------|-------|
| 44 | Mary (first meeting) | script_1001 |
| 46 | Popuri | script_1002 |
| 48 | Elli | script_1003 |
| 50 | Aqua / Harvest Sprite | script_1004 "Aqua" |
| 53 | Karen | script_1005 |
| 55 | Ann / Ran | script_1000 |
| 64 | Ellen | script_1006 |
| 70 | Stu | script_1007 |
| 79 | Sasha | script_1009 |
| 83 | Rick | script_1010 |
| 87 | Ann / Ran | script_1011 (main) |
| 95 | Barley | script_1012 |
| 104 | Duke (?) | script_1014 |
| 110 | Anna | script_1015 |
| 114 | Won | script_1016 |
| 118 | Lillia (?) | script_1017 |
| 121 | Mary | script_1018 (main) |
| 128 | Manna (?) | script_1019 |
| 133 | Harris | script_1020 |
| 138 | Manna | script_1021 |
| 142 | Thomas (?) | script_1022 |
| 145 | Basil | script_1023 |
| 149 | Carter | script_1024 |
| 153 | Gray (?) | script_1025 |
| 160 | Cliff (?) | script_1026 |
| 168 | Saibara | script_1027 |
| 172 | Gotz | script_1028 |
| 177 | May | script_1029 |

---

## 2. Dialogue Branch Conditions

### Common Condition Functions

| Function | Description |
|----------|-------------|
| `Func03E(N)` | Check event flag `N` (true/false) |
| `Func064()` | Check if player is riding a horse |
| `GetEntityFacing(N)` | Get direction the entity is facing |
| `GetEntityGender(N)` | Get entity gender |
| `GetSeason()` | Get current season (0=spring,1=summer,2=autumn,3=winter) |
| `GetTimeHour()` | Get current hour |
| `Func10A(type, id)` | Check animal affection level |
| `Func10C(type, id)` | Check if animal is pregnant |
| `Func10D(type, id)` | Get days until birth |
| `Func106()` | Get selected animal index |
| `HasAnimalBeenTalkedTo(type, id)` | Check if animal was talked to today |

### Friendship/Heart Conditions

Most NPC dialogue trees branch based on friendship level. The pattern is:

```c
if Func03E(FLAG_X)  // specific heart event flag
{
    // heart event dialogue
}
else if Func03E(FLAG_Y)
{
    // lower friendship dialogue
}
else
{
    // default dialogue
}
```

### Event Flag Range

Event flags are checked with `Func03E(FlagID)`. The flag range is not fully
documented, but event/relationship flags appear to use values in the range
~1–200 for basic events and higher for NPC-specific flags.

---

## 3. RAM Verification Addresses

Use these addresses (Stage 1, before loading a save) to verify conditions
when testing dialogue changes in an emulator:

### Time & Weather

| Address | Field | Size |
|---------|-------|------|
| `0x020025E0` | Current weather | 1 byte |
| `0x020025E8` | Year | 1 byte |
| `0x020025E9` | Day | 1 byte |
| `0x020025EA` | Hour | 1 byte |
| `0x020025EB` | Minute | 1 byte |

### Player

| Address | Field | Size |
|---------|-------|------|
| `0x02004080` | Money | 4 bytes |
| `0x020041B0` | Player name | 12 bytes |
| `0x020025EC` | Farm name | 12 bytes |

### NPC Affection

| Address | Character | Size |
|---------|-----------|------|
| `0x02004358` | Popuri | 2 bytes |
| `0x02004414` | Mary | 2 bytes |
| `0x020044A4` | Karen | 2 bytes |
| `0x020044D0` | Elli | 2 bytes |
| `0x02004524` | Ann | 2 bytes |
| `0x020045A4` | Goddess | 2 bytes |
| `0x02004324` | Lillia | 1 byte |
| `0x02004338` | Rick | 1 byte |
| `0x02004364` | Barley | 1 byte |
| `0x02004378` | May | 1 byte |
| `0x0200438C` | Saibara | 1 byte |
| `0x020043A4` | Gray | 1 byte |
| `0x020043B8` | Duke | 1 byte |
| `0x020043CC` | Manna | 1 byte |
| `0x020043E0` | Basil | 1 byte |
| `0x020043F4` | Anna | 1 byte |
| `0x02004420` | Thomas | 1 byte |
| `0x02004434` | Harris | 1 byte |
| `0x02004448` | Ellen | 1 byte |
| `0x0200445C` | Stu | 1 byte |
| `0x02004470` | Jeff | 1 byte |
| `0x02004484` | Sasha | 1 byte |
| `0x020044B0` | Doctor | 1 byte |
| `0x020044DC` | Carter | 1 byte |
| `0x020044F0` | Cliff | 1 byte |
| `0x02004504` | Doug | 1 byte |
| `0x02004530` | Kai | 1 byte |
| `0x02004544` | Gotz | 1 byte |
| `0x0200455C` | Zack | 1 byte |
| `0x02004570` | Won | 1 byte |
| `0x020045C4` | Lou/Ban | 1 byte |
| `0x020045DC` | Lu/Rubi | 1 byte |

---

## 4. Dialogue Modification Workflow

### Step 1: Find the NPC's script

1. Identify the NPC's `Proc030` speaker ID from the table above.
2. Search `scripts/*.mary` for `Proc030(NPC_ID)` to find the relevant scripts.
3. Each NPC typically has one main interaction script (1000-range) and may
   appear in festival/event scripts (1040–1100+).

### Step 2: Locate the dialogue text

Each script defines `MESSAGE_N` constants at the top. The branching logic
below uses `TalkMessage(MESSAGE_N)` to display specific dialogue.

### Step 3: Modify the text

Edit the `MESSAGE_N = "..."` string. Keep these constraints:
- Total script recompile size must fit the original script's ROM slot.
- Text encoding: `\r\n` for line breaks, `\x05` to end a message box.
- The `make check-script-patches` target verifies slot sizes.

### Step 4: Rebuild and test

```bash
make -j2 fomt.gba
make check-script-patches
# Then run in emulator: mgba-qt fomt.gba
```

### Step 5: Verify with RAM addresses

In an emulator (mGBA recommended), open the RAM viewer and check:
- Affection address for the NPC is at the expected level for the dialogue
- Time/weather match the event script's conditions
- Event flags can be identified by toggling and observing behavior changes

---

## 5. Example: Modifying Mary's Dialogue

Mary's main interaction script is `script_1018.mary` (Proc030(121)).

Her dialogue branches:
- Friendship level checks via `Func03E(event_flag)` determines which
  dialogue set is shown
- Higher affection → more friendly/romantic dialogue
- Birthday detection → birthday dialogue

To change her greeting:
1. Edit `scripts/script_1018.mary`
2. Find the `MESSAGE_N` constant with the current greeting
3. Modify the string (stay within slot size limit)
4. Run `make -j2 fomt.gba`
5. Test in emulator

---

## 6. Caveats

- mary script cross-references in `docs/generated/script_xref_index.tsv` can
  help find all scripts a specific NPC ID appears in.
- NPC appearance in festival scripts is seasonal — check `GetSeason()`
  conditions in the script.
- Some event scripts span multiple `.mary` files (event chains). Modify all
  parts of the chain to avoid broken sequences.
- The RAM addresses listed above are Stage 1. Stage 2 = Stage 1 + 0x2834.
