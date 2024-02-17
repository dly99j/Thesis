cmake_minimum_required(VERSION 3.27)
project(thesis_space_shooter)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(thesis_space_shooter src/main.cpp
        src/game.cpp
        incl/game.hpp
        src/movable.cpp
        incl/movable.hpp
        src/player_ship.cpp
        incl/player_ship.hpp
        incl/projectile.hpp
        src/projectile.cpp
)

target_link_libraries(thesis_space_shooter sfml-graphics sfml-window sfml-system OpenGL::GL OpenGL::GLU)
target_include_directories(thesis_space_shooter PRIVATE ${SFML_INCLUDE_DIR})
