cmake_minimum_required(VERSION 3.5.1)  
project(sudoku)               
set(CMAKE_CXX_STANDARD 14)            


set(SOURCE_FILES src/main.cpp src/Grid.cpp)

add_executable(sudoku ${SOURCE_FILES})