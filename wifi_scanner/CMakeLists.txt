cmake_minimum_required(VERSION 2.8.3)
project(wifi_scanner)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=gnu++0x -Os -fPIC")

FIND_LIBRARY( LIBIW_LIBRARY iw )
FIND_PATH(LIBIW_INCLUDE_DIR NAMES iwlib.h)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

 add_message_files(
   FILES
#   Message1.msg
#   Message2.msg
    wifi_signal_msg.msg
 )


 generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES wifi_scanner
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
   CATKIN_DEPENDS message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${LIBIW_INCLUDE_DIR}
)

include_directories(include ${catkin_INCLUDE_DIRS})


ADD_LIBRARY(wifi_scan SHARED ${PROJECT_SOURCE_DIR}/src/wifi_scanner.cpp)
TARGET_LINK_LIBRARIES( wifi_scan ${LIBIW_LIBRARY} )

add_executable(scan_wifi src/test_wifi_scanner.cpp)
target_link_libraries(scan_wifi ${catkin_LIBRARIES})
TARGET_LINK_LIBRARIES( scan_wifi wifi_scan)

add_dependencies(scan_wifi wifi_scanner_generate_messages_cpp)
