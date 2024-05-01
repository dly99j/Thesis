cmake_minimum_required(VERSION 3.27)
project(thesis_space_shooter)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
#find_package(Clang 19 REQUIRED CONFIG)
#find_package(LLVM 19 REQUIRED CONFIG)

#include_directories(${LLVM_INCLUDE_DIRS})
#add_definitions(${LLVM_DEFINITIONS})

include_directories(${CLANG_INCLUDE_DIRS})
add_definitions(${CLANG_DEFINITIONS})
add_executable(thesis_space_shooter
        src/main.cpp
        src/playing_state.cpp
        incl/playing_state.hpp
        src/movable.cpp
        incl/movable.hpp
        src/player_ship.cpp
        incl/player_ship.hpp
        incl/projectile.hpp
        src/projectile.cpp
        src/enemy_ship.cpp
        incl/enemy_ship.hpp
        src/ship_base.cpp
        incl/ship_base.hpp
        src/chasing_enemy.cpp
        incl/chasing_enemy.hpp
        src/powerup.cpp
        incl/powerup.hpp
        src/game.cpp
        incl/game.hpp
        incl/constants.hpp
        src/waypoint_enemy.cpp
        incl/waypoint_enemy.hpp
        src/main_menu.cpp
        incl/main_menu.hpp
        src/choose_map_state.cpp
        incl/choose_map_state.hpp
        incl/enums.hpp
        src/menu_base.cpp
        incl/menu_base.hpp
        src/avoiding_enemy.cpp
        incl/avoiding_enemy.hpp
        incl/music_player.hpp
        src/sound_player.cpp
        incl/sound_player.hpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

#target_link_libraries(thesis_space_shooter clang-cpp sfml-graphics sfml-window sfml-system)
target_link_libraries(thesis_space_shooter sfml-graphics sfml-window sfml-system sfml-audio)
target_include_directories(thesis_space_shooter PRIVATE ${SFML_INCLUDE_DIR})