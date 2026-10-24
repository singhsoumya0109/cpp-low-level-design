cmake_minimum_required(VERSION 3.16)
project(CppLowLevelDesign
    VERSION 1.0.0
    DESCRIPTION "The Definitive Self-Sufficient Low-Level Design & Design Patterns Repository in Modern C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wnon-virtual-dtor)
endif()

# Enable CTest
enable_testing()

message(STATUS "Configuring CppLowLevelDesign (C++17)")

# Include subdirectories dynamically if CMakeLists.txt exists
macro(add_subdirectories_if_exist dir)
    file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${dir} ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/${child})
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/${child}/CMakeLists.txt)
                add_subdirectory(${dir}/${child})
            endif()
        endif()
    endforeach()
endmacro()

add_subdirectories_if_exist("01-Creational-Patterns")
add_subdirectories_if_exist("02-Structural-Patterns")
add_subdirectories_if_exist("03-Behavioral-Patterns")
add_subdirectories_if_exist("04-Modern-Cpp-And-Extended-Patterns")
add_subdirectories_if_exist("07-LLD-Case-Studies")

