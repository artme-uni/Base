cmake_minimum_required(VERSION 3.13)
project(Base C)

set(CMAKE_C_STANDARD 99)

add_executable(Base main.c coder.c coder.h add.c add.h)