cmake_minimum_required(VERSION 3.16)
project(ejercicio1_primos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(ejercicio1_primos main.cpp)
target_link_libraries(ejercicio1_primos PRIVATE Qt6::Core)
