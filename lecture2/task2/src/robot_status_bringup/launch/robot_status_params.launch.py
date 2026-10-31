import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    params_path = os.path.join(
        get_package_share_directory('robot_status_bringup'), 'config', 'params.yaml')
    use_subscriber = LaunchConfiguration('use_subscriber')

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_subscriber',
            default_value='true',
            description='Whether to launch the subscriber',
        ),
        Node(
            package='robot_status_publisher',
            executable='robot_status_publisher',
            name='robot_status_publisher',
            parameters=[params_path],
            output='screen',
        ),
        Node(
            package='robot_status_subscriber',
            executable='robot_status_subscriber',
            name='robot_status_subscriber',
            output='screen',
            condition=IfCondition(use_subscriber),
        ),
    ])
