cmake_minimum_required(VERSION 3.23)
project(folder_terrorist)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)

set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_NAME} terrorist.cpp terrorist.h tests.cpp)
target_link_libraries(${TEST_NAME} PRIVATE gtest_main)

add_executable(folder_terrorist main.cpp terrorist.cpp terrorist.h)
