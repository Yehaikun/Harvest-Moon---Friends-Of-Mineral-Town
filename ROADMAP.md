# FoMT Ultimate Modding Framework - 路线图

## 终极目标
实现完整的游戏修改框架：
- 任意添加/编辑建筑、地图、NPC
- 自由编写剧情、对白（不限字数）、事件、节日
- UI自定义
- ROM扩大到32MB

## 阶段规划

### 阶段1: ROM扩容 8MB→32MB 🔴 高优先级
- [ ] 修改GBA header，声明32MB ROM
- [ ] 调整linker script (fomt.lds)
- [ ] 验证GBA能读取32MB数据
- [ ] 更新free space跟踪
- 依赖: Makefile, fomt.lds, linker知识

### 阶段2: Entity/Trigger系统 🟡 关键
- [ ] 逆向entity数据格式（map_id → 实体列表）
- [ ] 创建entity编辑工具 (tools/entity_editor.py)
- [ ] 实现map 63回传机制
- [ ] 脚本→tile映射工具
- 依赖: 阶段1（需要空间放新entity数据）

### 阶段3: 文字/对话系统 🟡 关键
- [ ] 定位游戏中所有文本数据
- [ ] 创建文本导出/导入工具
- [ ] 解除字数限制
- [ ] 支持中文/任意语言
- 依赖: 阶段1（更多空间）

### 阶段4: 地图编辑工具链 🟢
- [ ] 可视化tilemap编辑器
- [ ] 新地图从头创建向导
- [ ] tileset分析/编辑
- [ ] terrain/collision编辑
- 依赖: 阶段2

### 阶段5: NPC/角色系统 🟢
- [ ] NPC位置编辑
- [ ] NPC日程/路径编辑
- [ ] 新增NPC模板
- 依赖: 阶段2, 阶段4

### 阶段6: 事件/节日系统 🟢
- [ ] 事件脚本语言文档
- [ ] 新建节日/事件工具
- [ ] 过场动画编辑器
- 依赖: 阶段3, 阶段5

### 阶段7: UI自定义 🟢
- [ ] 菜单系统分析
- [ ] HUD元素编辑
- [ ] 自定义UI框架
- 依赖: 阶段1

## 验证标准
1. make clean && make -j2 fomt.gba ✅
2. make check-all ✅
3. mGBA 32MB ROM正常运行
4. 能进新地图/新建筑
5. NPC能说话（不限字数）
6. 自定义事件能触发
