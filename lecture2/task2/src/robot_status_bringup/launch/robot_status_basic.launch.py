from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    publisher = Node(
        package='robot_status_publisher',
        executable='robot_status_publisher',
        name='robot_status_publisher',
        output='screen',
    )

    subscriber = Node(
        package='robot_status_subscriber',
        executable='robot_status_subscriber',
        name='robot_status_subscriber',
        output='screen',
    )

    return LaunchDescription([publisher, subscriber])
