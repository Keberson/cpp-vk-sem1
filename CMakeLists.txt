cmake_minimum_required(VERSION 3.16)
project(set)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")

add_library(set SHARED
        include/set.h
        src/set.cpp)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_set
        tests/testSet.cpp)
target_link_libraries(test_set set)
target_link_libraries(test_set ${GTEST_LIBRARIES} pthread)

add_test(NAME SetTest
        COMMAND test_set)
