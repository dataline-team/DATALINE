cmake_minimum_required(VERSION 3.19)
project(DATALINE)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(lib/googletest)  # GTEST_DIR

find_package(Boost REQUIRED)  # BOOST_DIR
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find Boost")
    return()
else()
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_executable(DATALINE src/main.cpp)