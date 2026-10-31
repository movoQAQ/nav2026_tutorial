from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='robot_status_publisher',
            executable='robot_status_publisher',
            output='screen',
        )
    ])
