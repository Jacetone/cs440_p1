cmake_minimum_required(VERSION 3.14)
project(cs440)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs440
        Deque.hpp
        test.cpp)
target_link_libraries(cs440 "${CMAKE_DL_LIBS}")
