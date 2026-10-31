from launch import LaunchDescription
from launch.actions import GroupAction
from launch_ros.actions import Node, PushRosNamespace


def generate_launch_description():
    return LaunchDescription([
        GroupAction(actions=[
            PushRosNamespace('robot1'),
            Node(package='robot_status_publisher',
                 executable='robot_status_publisher', output='screen'),
            Node(package='robot_status_subscriber',
                 executable='robot_status_subscriber', output='screen'),
        ]),
    ])
