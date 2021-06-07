cmake_minimum_required(VERSION 3.17)
project(readable_libc C)

set(CMAKE_C_STANDARD 11)

add_executable(readable_libc main.c string_h.c)
