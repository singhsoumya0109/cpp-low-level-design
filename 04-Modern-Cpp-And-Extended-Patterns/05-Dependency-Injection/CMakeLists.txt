cmake_minimum_required(VERSION 3.15)
project(DependencyInjection LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(di_demo src/demo.cpp)
add_executable(test_di tests/test_dependency_injection.cpp)
add_test(NAME test_di COMMAND test_di)
