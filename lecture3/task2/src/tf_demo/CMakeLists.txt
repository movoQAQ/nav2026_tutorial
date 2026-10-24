cmake_minimum_required(VERSION 3.8)
project(tf_demo)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

add_executable(frame_broadcaster src/frame_broadcaster.cpp)
ament_target_dependencies(frame_broadcaster
  rclcpp geometry_msgs tf2 tf2_ros tf2_geometry_msgs)

add_executable(point_listener src/point_listener.cpp)
ament_target_dependencies(point_listener
  rclcpp geometry_msgs tf2 tf2_ros tf2_geometry_msgs)

install(TARGETS frame_broadcaster point_listener
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
