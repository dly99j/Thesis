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

find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED)
set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)

set(SOURCE_FILES
        ../thesis_space_shooter/incl/enums.hpp
        ../thesis_space_shooter/incl/config.hpp

        ../thesis_space_shooter/incl/movable.hpp
        ../thesis_space_shooter/src/movable.cpp

        ../thesis_space_shooter/incl/ship_base.hpp
        ../thesis_space_shooter/src/ship_base.cpp

        ../thesis_space_shooter/incl/player_ship.hpp
        ../thesis_space_shooter/src/player_ship.cpp

        ../thesis_space_shooter/incl/projectile.hpp
        ../thesis_space_shooter/src/projectile.cpp

        ../thesis_space_shooter/incl/enemy_ship.hpp
        ../thesis_space_shooter/src/enemy_ship.cpp

        ../thesis_space_shooter/incl/avoiding_enemy.hpp
        ../thesis_space_shooter/src/avoiding_enemy.cpp

        ../thesis_space_shooter/incl/waypoint_enemy.hpp
        ../thesis_space_shooter/src/waypoint_enemy.cpp

        ../thesis_space_shooter/incl/chasing_enemy.hpp
        ../thesis_space_shooter/src/chasing_enemy.cpp

        ../thesis_space_shooter/incl/chasing_enemy.hpp
        ../thesis_space_shooter/src/chasing_enemy.cpp

        Tests/ShipBaseTest.cpp
        Tests/PlayerShipTest.cpp
        Tests/EnemyShipTest.cpp
        Tests/AvoidingEnemyTest.cpp
        Tests/ChasingEnemyTest.cpp
        Tests/WaypointEnemyTest.cpp
)
include_directories(../thesis_space_shooter/incl)
add_executable(
        hello_test
        Tests/MovableTest.cpp
        Tests/ShipBaseTest.cpp
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
