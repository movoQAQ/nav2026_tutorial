cmake_minimum_required(VERSION 3.8)
project(qos_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# 下列 find_package 已存在时，不要再重复添加。
find_package(rclcpp REQUIRED)
find_package(visualization_msgs REQUIRED)

add_executable(marker_publisher src/marker_publisher.cpp)
target_compile_features(marker_publisher PUBLIC cxx_std_17)
ament_target_dependencies(marker_publisher rclcpp visualization_msgs)

install(TARGETS marker_publisher
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
