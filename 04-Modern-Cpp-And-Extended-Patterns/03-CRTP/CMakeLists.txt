cmake_minimum_required(VERSION 3.15)
project(CRTP LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(crtp_demo src/demo.cpp)
add_executable(test_crtp tests/test_crtp.cpp)
add_test(NAME test_crtp COMMAND test_crtp)
