cmake_minimum_required(VERSION 3.15)
project(NullObject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(null_object_demo src/demo.cpp)
add_executable(test_null_object tests/test_null_object.cpp)
add_test(NAME test_null_object COMMAND test_null_object)
