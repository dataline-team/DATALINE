file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lboost_serialization -pthread -lboost_log -fpermissive")

# Boost library
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS system filesystem serialization log REQUIRED)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find Boost")
    return()
else()
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_executable(
        ${BINARY}
        ${SOURCE_FILES}
        ${HEADER_FILES}
        Blank.h SerializeTypeIndexHandler.cpp SerializeTypeIndexHandler.h)

list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(
        ${BINARY}_lib
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

set_target_properties(
        ${BINARY} ${BINARY}_lib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)