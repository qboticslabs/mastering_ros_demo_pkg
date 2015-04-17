cmake_minimum_required(VERSION 2.8.3)
project(mastering_ros_demo_pkg)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
 actionlib 
  actionlib_msgs
  message_generation
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)

 add_message_files(
   FILES
   demo_msg.msg

 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   demo_srv.srv
 )

## Generate actions in the 'action' folder
 add_action_files(
   FILES
   Demo_action.action
 )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
   actionlib_msgs
 )


catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs actionlib actionlib_msgs message_runtime 
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)


include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_topic_publisher src/demo_topic_publisher.cpp)
target_link_libraries(demo_topic_publisher ${catkin_LIBRARIES})


include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_topic_subscriber src/demo_topic_subscriber.cpp)
target_link_libraries(demo_topic_subscriber ${catkin_LIBRARIES})


include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_msg_publisher src/demo_msg_publisher.cpp)
target_link_libraries(demo_msg_publisher ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_msg_subscriber src/demo_msg_subscriber.cpp)
target_link_libraries(demo_msg_subscriber ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_service_server src/demo_service_server.cpp)
target_link_libraries(demo_service_server ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_service_client src/demo_service_client.cpp)
target_link_libraries(demo_service_client ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_action_server src/demo_action_server.cpp)
target_link_libraries(demo_action_server ${catkin_LIBRARIES} )

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(demo_action_client src/demo_action_client.cpp)
target_link_libraries(demo_action_client ${catkin_LIBRARIES})




