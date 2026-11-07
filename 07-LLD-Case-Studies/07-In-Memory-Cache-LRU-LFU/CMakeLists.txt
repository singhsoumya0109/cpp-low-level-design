cmake_minimum_required(VERSION 3.15)
project(InMemoryCache LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cache_demo src/solution.cpp)
add_executable(test_cache tests/test_cache.cpp)
add_test(NAME test_cache COMMAND test_cache)
