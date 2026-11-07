cmake_minimum_required(VERSION 3.15)
project(OrderManagementSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(order_demo src/solution.cpp)
add_executable(test_order tests/test_order.cpp)
add_test(NAME test_order COMMAND test_order)
