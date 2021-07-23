cmake_minimum_required(VERSION 3.19)
project(DATALINE)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(lib/googletest)  # GTEST_DIR

add_executable(DATALINE src/main.cpp)