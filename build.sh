#!/bin/bash
if ! [ -z $1 ]; then
    if [ $1 = 'rm' ]; then
        rm sudoku
        echo "Executable removed."
        exit 0
    fi
fi

cd impl
cmake .
make 

rm -rf Makefile CMakeCache.txt  CMakeFiles/ cmake_install.cmake sudoku_autogen/ *.cpp

mv sudoku ../

exit 0;