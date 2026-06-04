# FoMT Script API Reference

Total: 309 functions

| ID | Type | Name | Args |
|---|---|---|---|
| 0x002 | proc | SetEntityPosition | which_entity, x, y, facing |
| 0x003 | func | GetEntityX | which_entity |
| 0x004 | func | GetEntityY | which_entity |
| 0x005 | proc | SetEntityFacing | which_entity, facing |
| 0x006 | func | GetEntityFacing | which_entity |
| 0x007 | proc | Proc007 | arg_1, arg_2 |
| 0x008 | proc | Proc008 | arg_1, arg_2, arg_3 |
| 0x009 | proc | Proc009 | arg_1, arg_2, arg_3 |
| 0x00A | proc | Proc00A | arg_1, arg_2, arg_3 |
| 0x00B | proc | Proc00B | arg_1, arg_2, arg_3 |
| 0x00C | proc | Proc00C | arg_1 |
| 0x00D | proc | SetEntityAnim | which_entity, arg_2 |
| 0x00F | proc | Proc00F | arg_1 |
| 0x010 | proc | Proc010 | arg_1, arg_2 |
| 0x011 | proc | Proc011 | arg_1, arg_2, arg_3 |
| 0x012 | proc | Proc012 | arg_1 |
| 0x013 | func | GetOppositeFacing | facing |
| 0x014 | func | GetEntityLocation | arg_1 |
| 0x015 | proc | Proc015 | arg_1, arg_2, arg_3 |
| 0x016 | proc | Proc016 | arg_1, arg_2, arg_3 |
| 0x017 | proc | Proc017 | arg_1, arg_2, arg_3 |
| 0x018 | proc | Proc018 |  |
| 0x019 | proc | PlayBGM | arg_1, arg_2 |
| 0x01A | proc | StopBGM |  |
| 0x01B | proc | PlaySong | arg_1, arg_2 |
| 0x01C | proc | StopAllSongs |  |
| 0x01D | proc | FadeOutBGM |  |
| 0x01F | proc | TalkOpen |  |
| 0x020 | proc | TalkClose |  |
| 0x021 | proc | TalkMessage | arg_1: string |
| 0x022 | proc | TalkMessageSlow | arg_1: string |
| 0x023 | proc | Proc024 | arg_1: string |
| 0x024 | func | Func025 | arg_1: string, arg_2: string, arg_3: string |
| 0x026 | func | Func027 | arg_1: string, arg_2: string, arg_3: string, arg_4: string, arg_5: string |
| 0x027 | func | TalkChoice2 | arg_1: string, arg_2: string |
| 0x028 | func | TalkChoice3 | arg_1: string, arg_2: string, arg_3: string |
| 0x029 | func | TalkChoice4 | arg_1: string, arg_2: string, arg_3: string, arg_4: string |
| 0x02A | func | TalkChoice5 | arg_1: string, arg_2: string, arg_3: string, arg_4: string, arg_5: string |
| 0x02B | func | TalkChoice6 | arg_1: string, arg_2: string, arg_3: string, arg_4: string, arg_5: string, arg_6: string |
| 0x02C | proc | Proc02D | arg_1 |
| 0x02D | proc | Proc02E | arg_1: string |
| 0x02E | proc | Proc02F |  |
| 0x02F | proc | Proc030 | arg_1 |
| 0x030 | proc | Proc031 |  |
| 0x031 | proc | Proc032 | arg_1 |
| 0x033 | proc | Proc034 | arg_1, arg_2 |
| 0x034 | proc | Proc035 | arg_1, arg_2 |
| 0x035 | proc | Proc036 | arg_1, arg_2 |
| 0x036 | proc | Proc037 | arg_1 |
| 0x037 | proc | Proc038 | arg_1 |
| 0x038 | proc | Proc039 | arg_1, arg_2 |
| 0x039 | proc | Proc03A | arg_1, arg_2, arg_3 |
| 0x03A | proc | Proc03B | arg_1, arg_2: string |
| 0x03C | func | Func03D | arg_1, arg_2 |
| 0x03D | func | Func03E | arg_1 |
| 0x03E | proc | Proc03F | arg_1, arg_2 |
| 0x03F | func | Func040 |  |
| 0x040 | func | Func041 |  |
| 0x041 | func | Func042 |  |
| 0x042 | func | Func043 |  |
| 0x043 | func | Func044 |  |
| 0x044 | func | Func045 |  |
| 0x045 | proc | Proc046 |  |
| 0x046 | proc | Proc047 |  |
| 0x047 | proc | Proc048 | arg_1 |
| 0x048 | proc | Proc049 | arg_1 |
| 0x049 | proc | Proc04A | arg_1 |
| 0x04A | proc | Proc04B | arg_1 |
| 0x04B | func | Func04C |  |
| 0x04C | func | Func04D |  |
| 0x04D | proc | Proc04E |  |
| 0x04E | func | Func04F |  |
| 0x04F | func | Func050 |  |
| 0x050 | proc | Proc051 | arg_1, arg_2 |
| 0x051 | proc | Proc052 |  |
| 0x052 | func | Func053 | arg_1 |
| 0x053 | func | Func054 | arg_1 |
| 0x054 | proc | Proc055 | arg_1 |
| 0x055 | func | Func056 |  |
| 0x056 | func | Func057 |  |
| 0x058 | func | Func059 | arg_1, arg_2 |
| 0x059 | func | Func05A | arg_1, arg_2 |
| 0x05A | proc | Proc05B | arg_1 |
| 0x05B | proc | Proc05C | arg_1, arg_2 |
| 0x05C | func | Func05D |  |
| 0x05D | func | Func05E | arg_1 |
| 0x05F | func | Func060 | arg_1 |
| 0x060 | proc | Proc061 | arg_1 |
| 0x061 | proc | Proc062 |  |
| 0x062 | proc | Proc063 |  |
| 0x063 | func | Func064 |  |
| 0x064 | proc | Proc065 |  |
| 0x065 | proc | Proc066 |  |
| 0x066 | proc | Proc067 |  |
| 0x067 | proc | Proc068 |  |
| 0x068 | func | Func069 |  |
| 0x069 | proc | Proc06A |  |
| 0x06A | proc | Proc06B |  |
| 0x06B | proc | Proc06C |  |
| 0x06C | func | Func06D |  |
| 0x06D | func | Func06E |  |
| 0x06E | func | Func06F |  |
| 0x070 | func | Func071 | arg_1 |
| 0x072 | proc | Proc073 |  |
| 0x073 | func | Func074 |  |
| 0x074 | proc | Proc075 |  |
| 0x076 | proc | Proc077 | arg_1 |
| 0x077 | func | Func07A | arg_1 |
| 0x078 | func | Func07B | arg_1 |
| 0x079 | proc | Proc07C | arg_1 |
| 0x07A | proc | Proc07D | arg_1 |
| 0x07B | func | Func07E | arg_1 |
| 0x07C | func | Func07F | arg_1 |
| 0x07D | proc | Proc080 | arg_1, arg_2 |
| 0x07E | proc | Proc081 | arg_1, arg_2 |
| 0x07F | func | Func082 | arg_1 |
| 0x080 | proc | Proc083 | arg_1 |
| 0x081 | func | Func084 | arg_1 |
| 0x082 | func | Func085 | arg_1 |
| 0x083 | func | Func086 | arg_1 |
| 0x084 | proc | Proc087 | arg_1 |
| 0x085 | func | Func088 | arg_1 |
| 0x086 | func | Func089 | arg_1 |
| 0x087 | proc | Proc08A | arg_1, arg_2 |
| 0x089 | proc | Proc08C | arg_1, arg_2 |
| 0x08A | proc | Proc08D | arg_1 |
| 0x08B | proc | Proc08E |  |
| 0x08C | proc | Proc08F | arg_1 |
| 0x08D | proc | Proc090 |  |
| 0x08E | proc | Proc091 |  |
| 0x08F | proc | Proc092 |  |
| 0x090 | proc | Proc093 |  |
| 0x091 | proc | Proc094 |  |
| 0x092 | proc | Proc095 |  |
| 0x093 | proc | Proc096 |  |
| 0x094 | proc | Proc097 |  |
| 0x095 | proc | Proc098 |  |
| 0x096 | proc | Proc099 |  |
| 0x097 | proc | Proc09A |  |
| 0x098 | proc | Proc09B | arg_1 |
| 0x099 | proc | Proc09C |  |
| 0x09A | proc | Proc09D |  |
| 0x09B | proc | Proc09E |  |
| 0x09C | proc | Proc09F |  |
| 0x09D | proc | Proc0A0 |  |
| 0x09E | proc | Proc0A1 |  |
| 0x09F | proc | Proc0A2 |  |
| 0x0A0 | proc | Proc0A3 |  |
| 0x0A1 | proc | Proc0A4 |  |
| 0x0A2 | func | Func0A5 |  |
| 0x0A3 | proc | Proc0A6 | arg_1, arg_2 |
| 0x0A4 | proc | Proc0A7 |  |
| 0x0A5 | proc | Proc0A8 |  |
| 0x0A6 | proc | Proc0A9 | arg_1 |
| 0x0A7 | func | Func0AA | arg_1 |
| 0x0A8 | proc | Proc0AB |  |
| 0x0A9 | proc | Proc0AC | arg_1 |
| 0x0AA | proc | Proc0AD |  |
| 0x0AB | proc | Proc0AE |  |
| 0x0AC | proc | Proc0AF |  |
| 0x0AD | proc | Proc0B0 |  |
| 0x0AE | proc | Proc0B1 |  |
| 0x0AF | proc | Proc0B2 |  |
| 0x0B0 | func | Func0B3 |  |
| 0x0B1 | func | Func0B4 | arg_1 |
| 0x0B2 | func | Func0B5 |  |
| 0x0B3 | proc | Proc0B6 | arg_1 |
| 0x0B4 | func | Func0B7 | arg_1 |
| 0x0B5 | proc | Proc0B8 | arg_1 |
| 0x0B6 | func | Func0B9 |  |
| 0x0B7 | func | Func0BA | arg_1 |
| 0x0B8 | proc | Proc0BB | arg_1 |
| 0x0B9 | proc | Proc0BC | arg_1 |
| 0x0BA | func | Func0BD | arg_1 |
| 0x0BB | func | Func0BE |  |
| 0x0BC | func | Func0BF | arg_1 |
| 0x0BD | func | Func0C0 | arg_1 |
| 0x0BE | func | Func0C1 | arg_1 |
| 0x0BF | proc | Proc0C2 | arg_1 |
| 0x0C0 | proc | Proc0C3 |  |
| 0x0C1 | func | Func0C4 |  |
| 0x0C2 | func | Func0C5 | arg_1 |
| 0x0C3 | func | Func0C6 | arg_1 |
| 0x0C4 | proc | Proc0C7 |  |
| 0x0C5 | proc | Proc0C8 |  |
| 0x0C6 | func | Func0C9 |  |
| 0x0C7 | proc | Proc0CA | arg_1 |
| 0x0C8 | proc | Proc0CB | arg_1 |
| 0x0C9 | proc | Proc0CC |  |
| 0x0CA | proc | Proc0CD |  |
| 0x0CB | func | Func0CE | arg_1 |
| 0x0CC | func | Func0CF | arg_1 |
| 0x0CD | func | Func0D0 | arg_1, arg_2 |
| 0x0CE | func | Func0D1 | arg_1 |
| 0x0D0 | proc | Proc0D3 | arg_1, arg_2, arg_3 |
| 0x0D1 | proc | Proc0D4 | arg_1 |
| 0x0D2 | func | Func0D5 | arg_1 |
| 0x0D3 | func | Func0D6 | arg_1 |
| 0x0D4 | func | Func0D7 | arg_1 |
| 0x0D5 | func | Func0D8 | arg_1 |
| 0x0D6 | func | Func0D9 |  |
| 0x0D7 | func | Func0DA | arg_1 |
| 0x0D8 | proc | Proc0DB | arg_1 |
| 0x0D9 | proc | Proc0DC |  |
| 0x0DA | func | Func0DD | arg_1 |
| 0x0DB | proc | Proc0DE |  |
| 0x0DC | proc | Proc0DF |  |
| 0x0DD | func | Func0E0 |  |
| 0x0DE | func | Func0E1 |  |
| 0x0DF | func | Func0E2 |  |
| 0x0E0 | proc | Proc0E3 | arg_1 |
| 0x0E1 | proc | Proc0E4 |  |
| 0x0E2 | proc | Proc0E5 |  |
| 0x0E3 | func | Func0E6 |  |
| 0x0E4 | func | Func0E7 |  |
| 0x0E5 | func | Func0E8 |  |
| 0x0E6 | func | Func0E9 |  |
| 0x0E7 | func | Func0EA |  |
| 0x0E8 | func | Func0EB |  |
| 0x0E9 | func | Func0EC |  |
| 0x0EA | func | Func0ED |  |
| 0x0EC | func | Func0EF |  |
| 0x0ED | proc | Proc0F0 | arg_1 |
| 0x0EE | proc | Proc0F1 | arg_1 |
| 0x0EF | proc | Proc0F2 |  |
| 0x0F0 | proc | Proc0F3 |  |
| 0x0F1 | func | Func0F4 |  |
| 0x0F2 | func | Func0F5 |  |
| 0x0F3 | func | Func0F6 |  |
| 0x0F4 | proc | Proc0F7 | arg_1, arg_2 |
| 0x0F5 | func | Func0F8 | arg_1 |
| 0x0F6 | func | Func0F9 | arg_1 |
| 0x0F7 | proc | Proc0FA | arg_1 |
| 0x0F8 | proc | Proc0FB | arg_1 |
| 0x0F9 | func | Func0FC |  |
| 0x0FA | func | Func0FD |  |
| 0x0FB | func | Func0FE | arg_1: string |
| 0x0FC | proc | Proc0FF | arg_1 |
| 0x0FD | proc | Proc100 |  |
| 0x0FE | proc | Proc101 |  |
| 0x0FF | func | Func102 | arg_1, arg_2 |
| 0x100 | proc | Proc103 | arg_1, arg_2, arg_3, arg_4, arg_5 |
| 0x101 | proc | Proc104 | arg_1, arg_2 |
| 0x102 | proc | GetAnimalName | string_slot, arg_2, arg_3 |
| 0x103 | func | Func106 |  |
| 0x104 | func | HasAnimalBeenTalkedTo | arg_1, arg_2 |
| 0x105 | proc | SetAnimalTalkedTo | arg_1, arg_2 |
| 0x106 | proc | Proc109 | arg_1, arg_2, arg_3 |
| 0x107 | func | Func10A | arg_1, arg_2 |
| 0x108 | func | GetAnimalAge | arg_1, arg_2 |
| 0x109 | func | Func10C | arg_1, arg_2 |
| 0x10A | func | Func10D | arg_1, arg_2 |
| 0x10C | func | Func10F | arg_1, arg_2 |
| 0x10D | func | Func110 | arg_1, arg_2 |
| 0x10E | func | Func111 | arg_1 |
| 0x10F | func | Func112 | arg_1, arg_2 |
| 0x110 | proc | Proc113 |  |
| 0x111 | proc | Proc114 |  |
| 0x112 | proc | Proc115 |  |
| 0x113 | proc | Proc116 |  |
| 0x114 | func | Func117 | arg_1 |
| 0x115 | func | Func118 |  |
| 0x116 | func | Func119 |  |
| 0x117 | func | Func11A |  |
| 0x118 | proc | Proc11B | arg_1, arg_2 |
| 0x119 | proc | Proc11C | arg_1 |
| 0x11A | func | Func11D | arg_1 |
| 0x11B | proc | Proc11E | arg_1 |
| 0x11C | func | Func11F |  |
| 0x11D | func | Func120 |  |
| 0x11E | func | Func121 |  |
| 0x11F | func | Func122 |  |
| 0x120 | func | Func124 |  |
| 0x121 | func | Func125 |  |
| 0x122 | func | Func126 |  |
| 0x123 | func | Func127 |  |
| 0x124 | func | Func128 |  |
| 0x125 | proc | Proc129 | arg_1: string |
| 0x126 | proc | Proc12A |  |
| 0x127 | proc | Proc12B | arg_1, arg_2, arg_3 |
| 0x128 | proc | Proc12C |  |
| 0x129 | proc | Proc12D |  |
| 0x12A | proc | Proc12E | arg_1 |
| 0x12B | proc | Proc12F |  |
| 0x12C | func | Func130 | arg_1 |
| 0x12D | proc | Proc131 |  |
| 0x12E | proc | Proc132 | arg_1, arg_2, arg_3, arg_4 |
| 0x12F | proc | Proc133 |  |
| 0x130 | proc | Proc134 |  |
| 0x131 | proc | Proc135 |  |
| 0x132 | proc | Proc136 |  |
| 0x133 | func | Func137 |  |
| 0x134 | proc | Proc138 | arg_1, arg_2 |
| 0x135 | proc | Proc139 |  |
| 0x136 | func | Func13A | arg_1 |
| 0x137 | func | Func13B | arg_1 |
| 0x138 | func | Func13C | arg_1 |
| 0x139 | proc | Proc13D | arg_1, arg_2, arg_3, arg_4, arg_5 |
| 0x13A | proc | Proc13E | arg_1 |
| 0x13B | func | Func13F | arg_1 |
| 0x13E | proc | Proc142 | arg_1, arg_2, arg_3, arg_4, arg_5 |
| 0x13F | proc | Proc143 | arg_1, arg_2, arg_3 |
| 0x140 | proc | Proc144 | arg_1, arg_2, arg_3 |
| 0x141 | proc | Proc145 | arg_1 |
| 0x142 | proc | Proc146 | arg_1 |
| 0x143 | proc | Proc147 | arg_1, arg_2, arg_3 |
| 0x144 | proc | Proc148 | arg_1, arg_2 |
| 0x145 | func | Func149 |  |
| 0x146 | proc | Proc14A |  |
