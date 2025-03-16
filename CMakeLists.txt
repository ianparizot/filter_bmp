cmake_minimum_required(VERSION 3.30)
project(filter_bmp C)

set(CMAKE_C_STANDARD 11)

add_executable(filter_bmp src/main.c
        src/bitmap.h
        src/functions.c
        src/functions.h
)
