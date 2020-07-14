cmake_minimum_required(VERSION 3.10)

# set the project name
project(helloword)

add_definitions(-std=c++11)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -Wl,-rpath=./:./lib:./lib/build/lib") #-Wl,-rpath=./
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wl,-rpath=./:./lib") #-Wall

# add the executable
add_executable(${PROJECT_NAME} main.cpp)

                                                                                                                                                                                                                                                       
# target_link_libraries(${PROJECT_NAME} hello)#默认连接动态库，如果连接动态库，执行时要保证能找到动态库
