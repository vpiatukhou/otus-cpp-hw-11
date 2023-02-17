set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(join_server_test ParserTest.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

target_include_directories(join_server_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(join_server_test join_server GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(join_server_test)
