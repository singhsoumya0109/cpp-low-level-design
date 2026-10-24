cmake_minimum_required(VERSION 3.16)
project(SingletonPattern CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(singleton_naive src/01-naive-approach.cpp)
add_executable(singleton_classic src/02-classic-pattern.cpp)
add_executable(singleton_realworld src/03-real-world-example.cpp)
add_executable(singleton_modern src/04-modern-cpp-style.cpp)

# Tests with multithreading
find_package(Threads REQUIRED)
add_executable(test_singleton tests/test_singleton.cpp)
target_link_libraries(test_singleton PRIVATE Threads::Threads)
add_test(NAME Test_Singleton COMMAND test_singleton)

