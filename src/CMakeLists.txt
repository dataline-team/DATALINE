file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(
        ${BINARY}
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

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