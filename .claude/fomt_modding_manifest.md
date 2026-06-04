# FoMT 终极修改框架 Manifest

## 目标
实现对游戏的全面控制：
- 人物位置/移动/行为控制
- 台词自由编写（不限字数）
- 事件/剧情自由创作
- 地形自由编辑
- 建筑自由添加/移动
- NPC自由创建
- UI自定义
- 节日自定义
- 游戏方方面面可编辑

## 已完成基础
✅ ROM 32MB扩容（~24MB free space）
✅ 地图扩展（农场65×60, 新地图60×60, 北镇352×176, 南镇260×96）
✅ 鸡屋→新地图传送 (script_167)
✅ 对话提取 (tools/extract_text.py, 1134脚本)
✅ 实体函数表定位 (0x080E602C, map 63已验证可修改)
✅ Ghidra装好可用
✅ 通用地图扩大器 (tools/expand_any_map.py)
✅ 新地图生成器 (tools/create_new_map.py)

## 执行顺序

### 第1阶段：Entity/Trigger回传 🎯
- 用Ghidra分析entity数据格式 (func_0808ECD8)
- 创建map 63回传实体（出口门）
- 自定义entity init函数
- 验证：鸡屋→新地图→回牧场

### 第2阶段：文本/对话修改 ✏️
- 文本写入工具（修改STR chunk）
- 支持中文/任意长度文本
- 脚本→文本映射可视化
- 验证：修改NPC对话

### 第3阶段：地形编辑 🗺️
- 可视化tilemap编辑器CLI
- terrain属性编辑
- tileset分析/替换
- 验证：地图上画新路径

### 第4阶段：建筑/实体编辑 🏠
- entity编辑器（位置/类型/脚本）
- 建筑添加/删除
- 门/传送点可视化编辑
- 验证：农场新增建筑

### 第5阶段：NPC/角色系统 👤
- NPC位置/日程编辑
- 新增NPC
- 对话树编辑器
- 验证：自定义NPC对话

### 第6阶段：事件/节日系统 🎉
- 节日脚本模板
- 自定义事件
- 过场动画控制
- 验证：新建节日

### 第7阶段：UI自定义 🖥️
- 菜单/对话框修改
- HUD元素
- 自定义UI框架
- 验证：修改标题画面

### 第8阶段：脚本引擎扩展 🔧
- ProcXX函数文档
- 新脚本命令
- 事件系统扩展
- 验证：自创剧情脚本

## Git规范
1. 永远别动main分支
2. 每个阶段从main开新分支: git switch -c mod/N main
3. 改前make clean && make -j2 fomt.gba
4. 每次提交make check-all通过
5. mGBA截图验证不白屏

## 验证标准
- make clean && make -j2 fomt.gba ✅
- make check-all ✅
- mGBA正常运行不白屏
- 新功能可实际使用
