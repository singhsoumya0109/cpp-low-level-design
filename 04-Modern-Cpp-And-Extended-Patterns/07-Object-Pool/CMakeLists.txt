cmake_minimum_required(VERSION 3.15)
project(ObjectPool LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(object_pool_demo src/demo.cpp)
target_link_libraries(object_pool_demo PRIVATE Threads::Threads)

add_executable(test_object_pool tests/test_object_pool.cpp)
target_link_libraries(test_object_pool PRIVATE Threads::Threads)
add_test(NAME test_object_pool COMMAND test_object_pool)
