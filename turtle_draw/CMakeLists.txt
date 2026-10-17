cmake_minimum_required(VERSION 3.5)
project(turtle_draw)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

add_executable(draw_flower src/draw_flower.cpp)
ament_target_dependencies(draw_flower rclcpp geometry_msgs turtlesim)

install(TARGETS
  draw_flower
  DESTINATION lib/${PROJECT_NAME})

ament_package()