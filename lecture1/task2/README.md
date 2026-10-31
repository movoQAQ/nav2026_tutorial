# Task 2：Topic 话题通信（完整代码）

对应本目录《Topic话题通信.html》，包含 C++ 和 Python 两套发布/订阅示例。
C++ 沿用仓库的 topic_publisher_cpp、topic_subscriber_cpp 分包结构，可执行文件名保持教程中的 topic_publisher_01、topic_subscribe_01；Python 包为 example_topic_rclpy。

本 task 的功能包直接位于 task2 下，colcon 可递归发现，无需移动目录。

```bash
source /opt/ros/humble/setup.bash
cd ~/nav2026_tutorial/lecture1/task2
colcon build --symlink-install
source install/setup.bash
ros2 run topic_subscriber_cpp topic_subscribe_01
```

另一个终端进入同一目录、source install/setup.bash 后运行：

```bash
ros2 run topic_publisher_cpp topic_publisher_01
```

C++ 每 0.5 秒发布 forward，订阅者输出速度 0.2。停止 C++ 示例后，分别在两个加载了同一工作空间的终端运行 Python 示例：

```bash
ros2 run example_topic_rclpy topic_subscribe_02
# 另一个终端：
ros2 run example_topic_rclpy topic_publisher_02
```

Python 每 0.5 秒发布 backup，订阅者输出速度 -0.2。两套示例共用 /command，均只打印速度，不驱动机器人。
验证命令：ros2 topic echo /command、ros2 topic info /command、ros2 run rqt_graph rqt_graph。
