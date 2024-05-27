cmake_minimum_required(VERSION 3.27)
project(thesis_space_shooter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_COMPILER "clang++")

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

if(NOT DEFINED SFML_DIR)
    set(SFML_DIR "C:/Program Files/SFML-2.6.1/lib/cmake/SFML")
endif()

find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_DIR}/lib)

set(SOURCES
        src/main.cpp
        src/playing_state.cpp
        src/movable.cpp
        src/player_ship.cpp
        src/projectile.cpp
        src/enemy_ship.cpp
        src/ship_base.cpp
        src/chasing_enemy.cpp
        src/powerup.cpp
        src/game.cpp
        src/waypoint_enemy.cpp
        src/main_menu.cpp
        src/choose_map_state.cpp
        src/menu_base.cpp
        src/avoiding_enemy.cpp
        src/sound_player.cpp
)

set(HEADERS
        incl/playing_state.hpp
        incl/movable.hpp
        incl/player_ship.hpp
        incl/projectile.hpp
        incl/enemy_ship.hpp
        incl/ship_base.hpp
        incl/chasing_enemy.hpp
        incl/powerup.hpp
        incl/game.hpp
        incl/config.hpp
        incl/waypoint_enemy.hpp
        incl/main_menu.hpp
        incl/choose_map_state.hpp
        incl/enums.hpp
        incl/menu_base.hpp
        incl/avoiding_enemy.hpp
        incl/music_player.hpp
        incl/sound_player.hpp
)

add_executable(thesis_space_shooter ${SOURCES} ${HEADERS})
target_link_libraries(thesis_space_shooter PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_include_directories(thesis_space_shooter PRIVATE ${SFML_INCLUDE_DIR})

if (WIN32)
    message(STATUS "Configuring for Windows")
elseif (APPLE)
    message(STATUS "Configuring for macOS")
elseif (UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux")
endif()