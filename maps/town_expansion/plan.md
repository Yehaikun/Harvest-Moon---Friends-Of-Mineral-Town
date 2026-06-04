# 城镇扩展 + 新地图计划

## 目标
1. 鸡屋 → 全新地图（3个初始房子）
2. 城镇扩大2倍（街道加宽，建筑顺延）
3. 其他地图按需调整

## 已知约束
- MapData共66个slot，全部已用。maps 63/64/65的terrain=0（可能是未使用）
- Free space: 636KB可用
- 北镇2倍: ~424KB, 南镇2倍: ~303KB
- 一次做不完所有，需要分阶段

## 阶段

### Phase A: 新地图（鸡屋传送）
1. 找一个可用map_id（maps 63/64/65，terrain=0未使用）
2. 创建30x30 tilemap：草地+3个简单房子
3. 创建terrain_map：房子周围不可走，其他可走
4. 用lzss4写入free space
5. 更新MapData entry（packed_tiles1/2/3, terrain_map, width, height）
6. 修改script_167：从鸡屋传送到新地图
7. 新地图添加回传：回到牧场门口
8. 验证：make clean && make -j2 && check-all && mGBA

### Phase B: 北镇扩大2倍（176x88→352x176）
1. 解压北镇3层tilemap
2. 扩大tilemap：每行边缘复制填充
3. 扩大terrain_map：同方法
4. 用lzss4写入free space
5. 更新MapData entry
6. 调整传送点坐标（warp_index.tsv里所有指向北镇的）
7. 验证

### Phase C: 南镇扩大2倍（173x64→346x128）
1. 同上方法
2. 验证

### 工具
- 复用 tools/patch_farm_expansion.py 的模式
- 创建 tools/patch_map_expansion.py（泛化版本）
- 创建 tools/map_creator.py（新地图生成器）

### 验证标准
1. make clean && make -j2 fomt.gba ✅
2. make check-all ✅
3. mGBA不白屏、不崩溃
4. 鸡屋进入新地图能看到3个房子
5. 能走回牧场
