from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, TimerAction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    use_subscriber = LaunchConfiguration('use_subscriber')

    publisher = Node(
        package='robot_status_publisher',
        executable='robot_status_publisher',
        output='screen',
    )
    subscriber = Node(
        package='robot_status_subscriber',
        executable='robot_status_subscriber',
        output='screen',
        condition=IfCondition(use_subscriber),
    )

    return LaunchDescription([
        DeclareLaunchArgument('use_subscriber', default_value='true'),
        subscriber,
        TimerAction(period=2.0, actions=[publisher]),
    ])
