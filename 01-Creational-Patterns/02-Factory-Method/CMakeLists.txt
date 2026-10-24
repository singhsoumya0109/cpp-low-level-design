cmake_minimum_required(VERSION 3.16)
project(FactoryMethodPattern CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(factory_naive src/01-naive-approach.cpp)
add_executable(factory_classic src/02-classic-pattern.cpp)
add_executable(factory_realworld src/03-real-world-example.cpp)
add_executable(factory_modern src/04-modern-cpp-style.cpp)

add_executable(test_factory_method tests/test_factory_method.cpp)
add_test(NAME Test_FactoryMethod COMMAND test_factory_method)
