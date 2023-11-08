#clang++ main.cpp -lLLVM-16 -lclang-cpp

cmake_minimum_required(VERSION 3.26)
project(Thesis)

set(CMAKE_CXX_STANDARD 20)

find_package(Clang 17 REQUIRED CONFIG)
find_package(LLVM 17 REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include_directories(${CLANG_INCLUDE_DIRS})
add_definitions(${CLANG_DEFINITIONS})

add_executable(Thesis main.cpp
                    MyASTVisitor.cpp
                    MyASTConsumer.cpp
                    MyFrontendAction.cpp)

target_link_libraries(Thesis PRIVATE LLVM-17 clang-cpp)

#if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
#endif()
