cmake_minimum_required(VERSION 3.16)
project(PrototypePattern CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prototype_naive src/01-naive-approach.cpp)
add_executable(prototype_classic src/02-classic-pattern.cpp)
add_executable(prototype_realworld src/03-real-world-example.cpp)
add_executable(prototype_modern src/04-modern-cpp-style.cpp)

add_executable(test_prototype tests/test_prototype.cpp)
add_test(NAME Test_Prototype COMMAND test_prototype)
