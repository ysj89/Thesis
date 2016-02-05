project(BT_test)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-Wall)


add_executable(${PROJECT_NAME} ${SRC_LIST})

