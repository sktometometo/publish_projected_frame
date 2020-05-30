cmake_minimum_required(VERSION 3.0.2)
project(publish_projected_frame)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  tf
  tf2
  tf2_ros
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES publish_projected_frame
#  CATKIN_DEPENDS geometry_msgs roscpp rospy tf tf2 tf2_ros
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(publish_projected_frame
    src/publish_projected_frame.cpp
)
target_link_libraries(publish_projected_frame
  ${catkin_LIBRARIES}
)
