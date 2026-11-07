cmake_minimum_required(VERSION 3.15)
project(VendingMachine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vending_demo src/solution.cpp)
add_executable(test_vending tests/test_vending.cpp)
add_test(NAME test_vending COMMAND test_vending)
