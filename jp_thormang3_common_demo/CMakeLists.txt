cmake_minimum_required(VERSION 2.8.3)
project(jp_thormang3_common_demo)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  std_msgs
)

catkin_package(
  INCLUDE_DIRS # include
  CATKIN_DEPENDS
  roscpp
  roslib
  std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} src/demo_node.cpp)
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
