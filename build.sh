#!/bin/bash

cd impl
cmake .
make

rm -r Makefile CMakeCache.txt  CMakeFiles/ cmake_install.cmake

mv sudoku ../

exit 0;