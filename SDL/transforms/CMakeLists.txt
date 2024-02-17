cmake_minimum_required(VERSION 3.26)
project(transforms)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#find_package(OpenSceneGraph REQUIRED)
#include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})


add_executable(transforms main.cpp generic_vector.hpp
        vec.hpp
        generic_matrix.hpp
        utils.hpp
        transform_matrix.hpp)
target_link_libraries(transforms ${SDL2_LIBRARIES})
#target_link_libraries(lecture_01 ${OPENSCENEGRAPH_LIBRARIES})
