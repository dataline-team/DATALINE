file(
        GLOB_RECURSE
        TEST_FILES
        LIST_DIRECTORIES
        false
        *.cpp *.h
)

include_directories(
        ../src
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)

set(BINARY gTest)
enable_testing()
add_executable(${BINARY} ${TEST_FILES})
add_test(${BINARY} ${BINARY})

target_link_libraries(
        ${BINARY}
        PUBLIC
        ${CMAKE_PROJECT_NAME}_lib
        gtest
)

add_custom_command(
        TARGET ${BINARY}
        COMMENT "Running tests"
        POST_BUILD
        COMMAND ${BINARY}
)
