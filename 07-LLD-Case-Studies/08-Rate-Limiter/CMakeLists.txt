cmake_minimum_required(VERSION 3.15)
project(RateLimiter LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rate_limiter_demo src/solution.cpp)
add_executable(test_rate_limiter tests/test_rate_limiter.cpp)
add_test(NAME test_rate_limiter COMMAND test_rate_limiter)
