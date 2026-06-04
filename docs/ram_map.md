# RAM Map — Harvest Moon: Friends of Mineral Town (GBA)

来源: https://datacrystal.tcrf.net/wiki/Harvest_Moon:_Friends_of_Mineral_Town/RAM_map

## 说明

RAM 地址分两个阶段:
- **Stage 1** = 未通过电池存档加载游戏
- **Stage 2** = 已加载存档 = Stage 1 + 0x2834

## 时间/天气

| Address | Field |
|---------|-------|
| `0x020025E0` | Weather |
| `0x020025E8` | Year |
| `0x020025E9` | Day |
| `0x020025EA` | Hour |
| `0x020025EB` | Minute |

## 金钱/资源

| Address | Field | Size |
|---------|-------|------|
| `0x02004080` | Money | 4 bytes |
| `0x020025FC` | Boards amount | 12 bits |

## NPC 好感度

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
