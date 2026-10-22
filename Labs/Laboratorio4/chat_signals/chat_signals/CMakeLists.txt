cmake_minimum_required(VERSION 3.16)
project(chat_signals LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(chat_signals main.cpp Comunicacion.cpp Comunicacion.h)
target_link_libraries(chat_signals PRIVATE Qt6::Core)
