from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    publisher = Node(
        package='robot_status_publisher',
        executable='robot_status_publisher',
        name='robot_status_publisher',
        output='screen',
            remappings=[('robot_status', 'robot_status_debug')],
    )

    subscriber = Node(
        package='robot_status_subscriber',
        executable='robot_status_subscriber',
        name='robot_status_subscriber',
        output='screen',
            remappings=[('robot_status', 'robot_status_debug')],
    )

    return LaunchDescription([publisher, subscriber])
