# 地图扩展计划进度

[X] 阶段0: 稳定基线 - ✅ 基线可用，check-all通过
[X] 阶段1: 地图数据总索引 - ✅ map_master_index.tsv + map_data_table.tsv
[X] 阶段2: 碰撞导出/修改验证 - ✅ terrain bit0已验证控制碰撞
[X] 阶段3: 视觉 tilemap 定位 - ✅ 已验证
    packed_img = tileset(1024 tiles, 32KB)
    packed_tiles1/2/3 = 3层tilemap(每层60x56x2B=6720B)
    GBA tilemap格式: 每格2字节 (tileindex+palette+flip)
[X] 阶段4: 地图边界/相机边界 - ✅ 
    max_camera_x = MapData.width*8 - 240
    max_camera_y = MapData.height*8 - 160
[X] 阶段5: 传送点和门 - ✅ warp_index.tsv 485条记录
[ ] 阶段6: 房屋扩建 - ❌ 待开始 需要组合tilemap+terrain修改
[X] 阶段7: free-space 重定位 - ✅ 655KB可用(0x75C244-0x800000)
[ ] 阶段8: 可复用地图包 - ❌ 待开始
[ ] 阶段9: 完整验收 - ❌ 待开始

已验证的关键链路:
- GetMapData(map_id) @ 0x080A4698
- MapData +0x00: packed_img = tileset (1024 tiles)
- MapData +0x04/0x08: packed_pal1/2 = palettes (480B)
- MapData +0x0C/0x10/0x14: packed_tiles1/2/3 = 3 tilemap layers (6720B each)
- MapData +0x18/0x1C: terrain_info/terrain_map = collision
- MapData +0x20/0x22: width/height = camera bounds
- ROM free space: 655KB at 0x75C244
