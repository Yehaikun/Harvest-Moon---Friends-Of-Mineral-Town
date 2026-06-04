# 地图扩展工具链路线图

## 已完成 (0-5+7)
- 地图索引: map_master_index.tsv + map_data_table.tsv
- 碰撞控制: terrain_info.bit0 已验证
- 相机边界: MapData.width/height * 8 - screen_size
- 传送索引: 485条 warp 记录
- tilemap 格式: 3层 x 60x56 x 2B = 6720B
- free space: 655KB 可用 (0x75C244)
- 地形修改: 已验证 terrain_map + width/height 可改

## 待完成 (6, 8, 9)

### 阶段6: 农场扩建 (需要 popuri 压缩器)
1. [ ] 实现 popuri 压缩器 (tools/scripts/compress.py)
   - 参照 decompress.py 逆向: atom_fmt(3)+lzss_fmt(3)+diff_fmt(3)
   - Huffman4/Huffman8 + LZSS + diff 编码
2. [ ] 修改 tilemap: 扩展 packed_tiles1 为 65x60x2B = 7800B
3. [ ] 重新压缩并写入 ROM (或放入 655KB free space)
4. [ ] 修改 terrain_map 为 65x60 = 3900B
5. [ ] 修改 MapData width=65 height=60
6. [ ] 更新 pointer 指向新数据位置
7. [ ] 编译验证

### 阶段8: 地图包化
1. [ ] 建立 maps/farm_expansion/patch.json 格式
2. [ ] 实现应用/回滚脚本

### 阶段9: 验收
1. [ ] make clean && make check-all
2. [ ] mGBA 进农场确认边界扩大
3. [ ] 不白屏、不走偏
