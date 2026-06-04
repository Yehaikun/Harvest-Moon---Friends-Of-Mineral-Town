# 地图扩展计划进度

[X] 阶段0: 稳定基线 - ✅ 基线可用，check-all通过
[X] 阶段1: 地图数据总索引 - ✅ map_master_index.tsv + map_data_table.tsv
[X] 阶段2: 碰撞导出/修改验证 - ✅ terrain bit0已验证控制碰撞
[ ] 阶段3: 视觉 tilemap 定位 - 🟡 部分完成
    packed_img解压为32768B=1024个GBA tile(像素数据),不是tilemap布局
    packed_tiles1/2/3有待进一步分析
    tilemap布局的定位需要反编译地图渲染加载函数
[ ] 阶段4: 地图边界/相机边界
[ ] 阶段5: 传送点和门
[ ] 阶段6: 房屋扩建
[ ] 阶段7: free-space 重定位
[ ] 阶段8: 可复用地图包
[ ] 阶段9: 完整验收
