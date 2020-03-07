cmake_minimum_required(VERSION 3.0.0)
project(example VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(example SHARED example.cpp)
target_compile_definitions(example PRIVATE example_EXPORTS=1)

add_executable(example_main main.cpp)
target_link_libraries(example_main example)