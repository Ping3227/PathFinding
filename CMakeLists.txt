cmake_minimum_required(VERSION 3.29)
project(PathFinding)

set(CMAKE_CXX_STANDARD 20)

add_executable(PathFinding main.cpp
        Grid.cpp
        Grid.h
        PathFinding.cpp
        PathFinding.h
)
