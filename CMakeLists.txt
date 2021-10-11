cmake_minimum_required(VERSION 3.20)
project(tee)

set(CMAKE_CXX_STANDARD 11)

add_executable(tee main.cpp tee.cpp tee.h)
