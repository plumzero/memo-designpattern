cmake_minimum_required(VERSION 3.0.2)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

include_directories(.)
add_executable(realize      realize.cpp)
target_link_libraries(realize pthread)
