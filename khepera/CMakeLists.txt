#project(khepera)
#cmake_minimum_required(VERSION 2.8)
#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})


project(khepera)
cmake_minimum_required(VERSION 2.8)
#aux_source_directory(. SRC_LIST)

file(GLOB SRC_LIST
    "*.h"
    "*.cpp"
    "../BT/*.h"
    "../BT/*.cpp"
    "../BT_leafs/*.h"
    "../BT_leafs/*.cpp"
    "../EvolutionaryLearning/GP.h"
    "../EvolutionaryLearning/GP.cpp"
    "../EvolutionaryLearning/GP_utils.h"
    "../EvolutionaryLearning/GP_utils.cpp"
)

add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-Wall)

add_executable(${PROJECT_NAME} ${SRC_LIST})
