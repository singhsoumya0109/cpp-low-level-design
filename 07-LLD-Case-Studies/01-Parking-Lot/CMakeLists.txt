cmake_minimum_required(VERSION 3.15)
project(ParkingLot LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(parking_lot_demo src/main.cpp)
target_link_libraries(parking_lot_demo PRIVATE Threads::Threads)

add_executable(test_parking_lot tests/test_parking_lot.cpp)
target_link_libraries(test_parking_lot PRIVATE Threads::Threads)
add_test(NAME test_parking_lot COMMAND test_parking_lot)
