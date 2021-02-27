cmake_minimum_required(VERSION 2.8)

project(Glad)
# set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> -o -c ")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(glad
    ./include/glad/glad.h
    ./src/glad.c
)

target_include_directories(glad PUBLIC include/)
