cmake_minimum_required(VERSION 3.27)
project(thesis_space_shooter)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(Clang 17 REQUIRED CONFIG)
find_package(LLVM 17 REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include_directories(${CLANG_INCLUDE_DIRS})
add_definitions(${CLANG_DEFINITIONS})

add_executable(thesis_space_shooter src/main.cpp
        src/game.cpp
        incl/game.hpp
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
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
target_link_libraries(thesis_space_shooter LLVM-17 clang-cpp sfml-graphics sfml-window sfml-system)
target_include_directories(thesis_space_shooter PRIVATE ${SFML_INCLUDE_DIR})