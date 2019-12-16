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

rm -r Makefile CMakeCache.txt  CMakeFiles/ cmake_install.cmake sudoku_autogen/

mv sudoku ../

exit 0;