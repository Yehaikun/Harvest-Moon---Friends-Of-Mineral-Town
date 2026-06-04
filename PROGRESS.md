# 地图扩展计划进度

[X] 阶段0: 稳定基线 - ✅ 基线可用，check-all通过
[X] 阶段1: 地图数据总索引 - ✅ map_master_index.tsv + map_data_table.tsv
[X] 阶段2: 碰撞导出/修改验证 - ✅ terrain bit0已验证控制碰撞
[ ] 阶段3: 视觉 tilemap 定位 - 🟡 部分完成
    packed_img = tile graphics(1024 tiles x 32B = 32KB), tilemap布局需分析渲染函数
[X] 阶段4: 地图边界/相机边界 - ✅ 已定位
    GetMapData(width/height)直接控制相机范围
    max_camera_x = MapData.width * 8 - 240
    max_camera_y = MapData.height * 8 - 160
    修改MapData.width/height后相机会允许滚动到新区域
[X] 阶段5: 传送点和门 - ✅ warp_index.tsv 485条记录覆盖全部地图
[ ] 阶段6-9: 需要进一步分析视觉tilemap、free-space扫描、打包和验收

已验证的关键链路:
- GetMapData(map_id) @ 0x080A4698 → 返回 MapData 结构体
- MapData +0x20/0x22 (width/height) → 控制相机边界
- MapData +0x18/0x1C (terrain_info/terrain_map) → 控制碰撞
- MapData +0x00 (packed_img) → tile图形数据(32KB解压后)
