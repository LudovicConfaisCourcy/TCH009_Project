cmake_minimum_required(VERSION 3.28.6)
project(Devoir_A2024_TCH009 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(Devoir_A2024_TCH009 main.c
        menu.h
        matrac_lib.h
        config.h
        menu.c
        matrac_lib.c
        test.c
        test.h)
