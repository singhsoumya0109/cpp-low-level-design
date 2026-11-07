cmake_minimum_required(VERSION 3.15)
project(Splitwise LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(splitwise_demo src/solution.cpp)
add_executable(test_splitwise tests/test_splitwise.cpp)
add_test(NAME test_splitwise COMMAND test_splitwise)
