cmake_minimum_required(VERSION 3.15)
project(MovieBookingSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(movie_demo src/solution.cpp)
add_executable(test_movie tests/test_movie.cpp)
add_test(NAME test_movie COMMAND test_movie)
