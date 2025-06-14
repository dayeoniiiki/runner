cmake_minimum_required(VERSION 3.8)
project(runner)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(behaviortree_cpp REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

include_directories(include)

add_executable(bt_main
  src/main.cpp
  src/MoveToGoalNode.cpp
  src/SetAngleNode.cpp
  src/WaitForResultNode.cpp
  src/CaptureImageNode.cpp
  src/SaveResultNode.cpp
  src/SetFailureReasonNode.cpp
  src/ReturnToBaseNode.cpp
  src/SendMetaDataNode.cpp
  src/WaitForStartNode.cpp
  src/CheckImageMatch.cpp               # ✅ 새로 추가한 노드
)

ament_target_dependencies(bt_main
  rclcpp
  behaviortree_cpp
)

install(TARGETS bt_main
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY behavior_trees
  DESTINATION share/${PROJECT_NAME}
)
