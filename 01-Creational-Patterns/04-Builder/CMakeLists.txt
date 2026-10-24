cmake_minimum_required(VERSION 3.16)
project(BuilderPattern CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(builder_naive src/01-naive-approach.cpp)
add_executable(builder_classic src/02-classic-pattern.cpp)
add_executable(builder_realworld src/03-real-world-example.cpp)
add_executable(builder_modern src/04-modern-cpp-style.cpp)

add_executable(test_builder tests/test_builder.cpp)
add_test(NAME Test_Builder COMMAND test_builder)
