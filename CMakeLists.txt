cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project (lidardriver)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

include_directories(include)

add_library(
    lidardriver
    include/lidardriver.hpp
    src/lidardriver.cpp
)

add_executable(
    lidardriver_tester
    src/main.cpp
)

target_link_libraries(
    lidardriver_tester
    lidardriver
)