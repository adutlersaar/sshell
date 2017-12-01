cmake_minimum_required(VERSION 3.8)
project(MyShell)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES myshell_main.c myshell.c)
add_executable(MyShell ${SOURCE_FILES})