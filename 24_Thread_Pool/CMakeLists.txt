cmake_minimum_required(VERSION 3.0.2)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

# RHEL 7.5 下编译有问题，后续再看
# add_executable(simple      simple.cpp)
# target_link_libraries(simple pthread)

include_directories(.)
add_executable(TestThdPool      TestThdPool.cpp)
target_link_libraries(TestThdPool pthread)