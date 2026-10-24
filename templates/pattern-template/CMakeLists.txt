cmake_minimum_required(VERSION 3.16)
project(PatternTemplate CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile executables
add_executable(pattern_naive src/01-naive-approach.cpp)
add_executable(pattern_classic src/02-classic-pattern.cpp)
add_executable(pattern_realworld src/03-real-world-example.cpp)
add_executable(pattern_modern src/04-modern-cpp-style.cpp)

# Tests
add_executable(test_pattern tests/test_pattern.cpp)
add_test(NAME Test_Pattern COMMAND test_pattern)

