cmake_minimum_required(VERSION 3.27)
project(hello_test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)

set(SOURCE_FILES
        ../thesis_space_shooter/incl/movable.hpp
        ../thesis_space_shooter/incl/ship_base.hpp
        ../thesis_space_shooter/src/movable.cpp
        ../thesis_space_shooter/src/ship_base.cpp
        ShipBaseTest.cpp
)
include_directories(../thesis_space_shooter/incl)
add_executable(
        hello_test
        MovableTest.cpp
        ShipBaseTest.cpp
        ${SOURCE_FILES}
)
target_link_libraries(
        hello_test
        gtest_main
        gmock
        ${SFML_LIBS}
)

include(GoogleTest)
gtest_discover_tests(hello_test)
