import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    share_dir = get_package_share_directory('robot_status_bringup')
    return LaunchDescription([
        DeclareLaunchArgument('use_subscriber', default_value='true'),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(
            os.path.join(share_dir, 'launch', 'publisher.launch.py'))),
        Node(package='robot_status_subscriber', executable='robot_status_subscriber',
             output='screen', condition=IfCondition(LaunchConfiguration('use_subscriber'))),
    ])
