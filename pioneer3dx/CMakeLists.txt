cmake_minimum_required(VERSION 2.8.3)
project(pioneer3dx)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(3dxControl src/KeyController.cpp)
target_link_libraries(3dxControl ${catkin_LIBRARIES})

add_executable(routerlisten src/listener.cpp)
target_link_libraries(routerlisten ${catkin_LIBRARIES})


