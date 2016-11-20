cmake_minimum_required(VERSION 3.6)
project(week7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    oxo.c)

add_executable(week7 ${SOURCE_FILES})