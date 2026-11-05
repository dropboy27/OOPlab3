cmake_minimum_required(VERSION 3.20)
project(lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

add_library(quadratic_set STATIC quadratic_set.cpp)

add_executable(lab3_app main.cpp)
target_link_libraries(lab3_app PRIVATE quadratic_set)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests test_quadratic_set.cpp)
target_link_libraries(run_tests PRIVATE quadratic_set gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(run_tests)