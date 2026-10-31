# Task 2：Launch 启动（完整代码）

教程原文件：[Launch启动.html](Launch启动.html)。四个功能包均已补齐；无需执行 HTML 中覆盖空白模板的 cp 命令。
本 task 独立编译，在新终端中只加载当前 task 的工作空间。

```bash
source /opt/ros/humble/setup.bash
cd ~/nav2026_tutorial/lecture2/task2
colcon build --symlink-install --packages-up-to robot_status_bringup
source install/setup.bash
ros2 launch robot_status_bringup robot_status.launch.py
```

默认每秒发布一次机器人状态，并同时启动订阅者。Ctrl+C 停止当前示例后再运行下一项。

| 教程内容 | 启动文件与参数 | 预期结果 |
| --- | --- | --- |
| 基础双节点 | robot_status_basic.launch.py | 两个节点、/robot_status |
| 条件启动（默认入口） | robot_status.launch.py use_subscriber:=false | 仅启动发布者 |
| 延时启动 | robot_status_delayed.launch.py | 订阅者立即启动，发布者延后 2 秒 |
| 双节点重映射 | robot_status_remap.launch.py | 话题 /robot_status_debug |
| 分组命名空间 | robot_status_namespace.launch.py | 话题 /robot1/robot_status |
| YAML 节点参数 | robot_status_params.launch.py | 加载 config/params.yaml，以 2 Hz 发布 |
| 子 Launch | robot_status_include.launch.py | Include publisher.launch.py，仅一个发布者 |

表中各项均使用 ros2 launch robot_status_bringup 加上对应文件名启动。
条件、延时、参数和 Include 版本支持 use_subscriber:=false。
publisher.launch.py 也可单独启动发布者。

在另一个加载了同一工作空间的终端检查：

```bash
ros2 node list
ros2 topic type /robot_status
ros2 topic echo /robot_status
ros2 topic info /robot_status --verbose
# YAML 示例专用：
ros2 param get /robot_status_publisher publish_frequency
ros2 topic hz /robot_status
# 查看默认入口参数：
ros2 launch robot_status_bringup robot_status.launch.py --show-args
```

消息固定为 id=1、battery_level=87.5、is_active=true。重映射或命名空间示例需换成表中的话题路径。
publish_frequency 只在启动时读取，不实现在线修改定时器；非正值回退至 1 Hz。
事件处理、替换符与组件容器为 HTML 阅读扩展，普通可执行节点不直接注册为组件插件。

## 验证范围

归档时完成 Python 语法、XML、消息字段、CMake 源文件/安装目标和 Launch 引用的静态检查。
归档机器没有 ROS 2 Humble/colcon，尚未进行实际 colcon 编译及 DDS 通信测试。上述命令用于在课程环境验收。
