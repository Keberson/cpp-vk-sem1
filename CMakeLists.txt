cmake_minimum_required(VERSION 3.16)
project(matrix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")

add_library(vector SHARED
        include/vector.h
        src/vector.cpp)

add_library(matrix SHARED
        include/matrix.h
        src/matrix.cpp)
target_link_libraries(matrix vector)


enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(matrix_calculator_test
        src/test.cpp)
target_link_libraries(matrix_calculator_test matrix)
target_link_libraries(matrix_calculator_test ${GTEST_LIBRARIES} pthread)

add_test(NAME MatrixCalculatorTest
        COMMAND matrix_calculator_test)