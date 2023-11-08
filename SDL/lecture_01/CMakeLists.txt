cmake_minimum_required(VERSION 3.26)
project(lecture_01)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#find_package(OpenSceneGraph REQUIRED)
#include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})


add_executable(lecture_01 main.cpp)
target_link_libraries(lecture_01 ${SDL2_LIBRARIES})
#target_link_libraries(lecture_01 ${OPENSCENEGRAPH_LIBRARIES})
