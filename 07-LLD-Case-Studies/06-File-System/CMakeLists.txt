cmake_minimum_required(VERSION 3.15)
project(FileSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fs_demo src/solution.cpp)
add_executable(test_fs tests/test_fs.cpp)
add_test(NAME test_fs COMMAND test_fs)
