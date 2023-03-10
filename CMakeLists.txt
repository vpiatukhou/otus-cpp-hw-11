cmake_minimum_required(VERSION 3.4.0)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(join_server VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(SQLITE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/sqlite)
set(DB_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources/join_server.db)

option(WITH_TESTS FALSE CACHE)

add_subdirectory(sqlite)
add_subdirectory(src)

if(${WITH_TESTS})
    add_subdirectory(test)
    enable_testing()
    add_test(NAME all_test COMMAND join_server_test)
endif()