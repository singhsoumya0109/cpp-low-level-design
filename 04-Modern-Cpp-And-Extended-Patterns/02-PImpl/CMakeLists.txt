cmake_minimum_required(VERSION 3.15)
project(PImpl LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pimpl_demo src/demo.cpp)
add_executable(test_pimpl tests/test_pimpl.cpp)
add_test(NAME test_pimpl COMMAND test_pimpl)
