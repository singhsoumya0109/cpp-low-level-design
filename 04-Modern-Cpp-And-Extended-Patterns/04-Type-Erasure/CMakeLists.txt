cmake_minimum_required(VERSION 3.15)
project(TypeErasure LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(type_erasure_demo src/demo.cpp)
add_executable(test_type_erasure tests/test_type_erasure.cpp)
add_test(NAME test_type_erasure COMMAND test_type_erasure)
