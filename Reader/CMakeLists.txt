cmake_minimum_required(VERSION 2.8.3)
project(reader)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=gnu++0x -Os -fPIC")

find_package(catkin REQUIRED COMPONENTS geometry_msgs roscpp rospy std_msgs tf)

catkin_package(CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs tf)

include_directories(include ${catkin_INCLUDE_DIRS})

ADD_LIBRARY(Node SHARED ${PROJECT_SOURCE_DIR}/src/Node.cpp)
ADD_LIBRARY(NodeList SHARED ${PROJECT_SOURCE_DIR}/src/NodeList.cpp)

add_executable(reader src/reader.cpp)
TARGET_LINK_LIBRARIES( reader Node NodeList )
TARGET_LINK_LIBRARIES( NodeList Node)

target_link_libraries(reader ${catkin_LIBRARIES})





if(catkin_EXPORTED_TARGETS)
  add_dependencies(reader ${catkin_EXPORTED_TARGETS})
endif()

