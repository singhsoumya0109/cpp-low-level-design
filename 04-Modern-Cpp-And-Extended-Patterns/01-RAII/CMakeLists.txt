cmake_minimum_required(VERSION 3.15)
project(RAII LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raii_demo src/demo.cpp)
target_include_directories(raii_demo PRIVATE src)

add_executable(test_raii tests/test_raii.cpp)
target_include_directories(test_raii PRIVATE src)
add_test(NAME test_raii COMMAND test_raii)
