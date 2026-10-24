from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    motion = ParameterValue(LaunchConfiguration('motion'), value_type=bool)
    use_sim_time = ParameterValue(
        LaunchConfiguration('use_sim_time'), value_type=bool)

    return LaunchDescription([
        DeclareLaunchArgument('motion', default_value='false'),
        DeclareLaunchArgument('use_sim_time', default_value='false'),
        Node(
            package='tf_demo',
            executable='frame_broadcaster',
            name='frame_broadcaster',
            parameters=[{'motion': motion, 'use_sim_time': use_sim_time}],
            output='screen',
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='static_laser_tf',
            arguments=[
                '--x', '0.2', '--y', '0.0', '--z', '0.3',
                '--roll', '0.0', '--pitch', '0.0', '--yaw', '0.0',
                '--frame-id', 'base_link', '--child-frame-id', 'laser_frame',
            ],
            parameters=[{'use_sim_time': use_sim_time}],
            output='screen',
        ),
        Node(
            package='tf_demo',
            executable='point_listener',
            name='point_listener',
            parameters=[{'use_sim_time': use_sim_time}],
            output='screen',
        ),
    ])
