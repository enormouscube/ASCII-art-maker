project( ASCII_ART_MAKER )
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 23)

add_executable( ASCII_ART_MAKER code.cpp lodepng/lodepng.cpp )