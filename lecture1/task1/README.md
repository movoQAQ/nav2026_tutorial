# Task 1：C++ 与 Python 功能包（完整代码）

对应本目录的《ROS2基础与功能包.html》。源码位于 src/first_package 和 src/first_py_package，均已补齐构建与安装配置。

在已安装 ROS 2 Humble、colcon 的 Ubuntu 22.04 终端中执行（仓库路径按实际位置替换）：

```bash
source /opt/ros/humble/setup.bash
cd ~/nav2026_tutorial/lecture1/task1
colcon build --symlink-install
source install/setup.bash
ros2 run first_package my_node
```

另开终端，加载同一工作空间后运行 Python 版本：

```bash
source /opt/ros/humble/setup.bash
cd ~/nav2026_tutorial/lecture1/task1
source install/setup.bash
ros2 run first_py_package my_node
```

预期分别输出 Hello ROS2 Node! 和 Hello ROS2 Python Node!，节点保持运行直至 Ctrl+C。
可用 ros2 node list 查看 /my_node 和 /my_py_node。

HTML 保留原始教程；其中 TRACE 日志示意不属于 Humble 的标准日志 API，示例节点未使用它。
每个 task 独立编译，不要在仓库根目录统一 colcon build。
