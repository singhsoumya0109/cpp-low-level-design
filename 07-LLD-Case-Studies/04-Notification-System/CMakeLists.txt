cmake_minimum_required(VERSION 3.15)
project(NotificationSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(notification_demo src/solution.cpp)
add_executable(test_notification tests/test_notification.cpp)
add_test(NAME test_notification COMMAND test_notification)
