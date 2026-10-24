cmake_minimum_required(VERSION 3.16)
project(AbstractFactoryPattern CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(abstract_factory_naive src/01-naive-approach.cpp)
add_executable(abstract_factory_classic src/02-classic-pattern.cpp)
add_executable(abstract_factory_realworld src/03-real-world-example.cpp)
add_executable(abstract_factory_modern src/04-modern-cpp-style.cpp)

add_executable(test_abstract_factory tests/test_abstract_factory.cpp)
add_test(NAME Test_AbstractFactory COMMAND test_abstract_factory)
