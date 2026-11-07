cmake_minimum_required(VERSION 3.15)
project(ElevatorSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(elevator_demo src/solution.cpp)
target_link_libraries(elevator_demo PRIVATE Threads::Threads)

add_executable(test_elevator tests/test_elevator.cpp)
target_link_libraries(test_elevator PRIVATE Threads::Threads)
add_test(NAME test_elevator COMMAND test_elevator)
