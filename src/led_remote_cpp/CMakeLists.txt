cmake_minimum_required(VERSION 3.8)
project(led_remote_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

find_library(WIRINGPI_LIBRARY NAMES wiringPi)

add_executable(remote src/remote.cpp)

target_link_libraries(remote
  ${WIRINGPI_LIBRARY}
  pthread
)

ament_target_dependencies(remote rclcpp)

target_include_directories(remote PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  /usr/local/include  # Explicitly add the system include path
)

target_compile_features(remote PUBLIC cxx_std_17)

install(TARGETS remote
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
