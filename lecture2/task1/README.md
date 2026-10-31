# Task 1：自定义消息类型（完整代码）

教程原文件：[自定义消息类型.html](自定义消息类型.html)。本归档已完成其中的空白源码、消息生成、依赖和可执行文件安装配置，无需再次填写。

每个 task 是独立工作空间。task1 和 task2 都包含 custom_interfaces，不要从仓库或 lecture2 根目录统一编译，也不要在同一终端混合加载两个 task 的 install。

```bash
source /opt/ros/humble/setup.bash
cd ~/nav2026_tutorial/lecture2/task1
colcon build --symlink-install
source install/setup.bash
ros2 interface show custom_interfaces/msg/RobotStatus
ros2 run custom_msg_demo robot_status_publisher
```

另开终端进入同一 task、加载 ROS 和 install/setup.bash 后运行：

```bash
ros2 run custom_msg_demo robot_status_subscriber
```

预期每秒收到 id=1、battery_level=87.5、is_active=true。
另一个终端可执行 ros2 topic echo /robot_status 和 ros2 topic info /robot_status --verbose。
