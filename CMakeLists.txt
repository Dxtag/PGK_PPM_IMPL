cmake_minimum_required(VERSION 3.20)
project(untitled5)
set(CMAKE_CXX_STANDARD 17)
add_executable(untitled5 main.cpp
        PPM/PPM.cpp
        funcs/funcs.cpp
        PPM/PPM.h
        PPM/BMP.h
        PPM/BMP.cpp
        funcs/funcs.h
        tests/tests.cpp
        tests/tests.h
)