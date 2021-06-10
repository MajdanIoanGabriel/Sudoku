#!/bin/bash

if ! test -x /usr/bin/qmake
then
    echo "Installing missing qt5 packages..."
    sudo apt-get install -y qt5-default >> /dev/null
fi

if ! [ -z $1 ]; then
    if [ $1 = 'rm' ]; then
        rm -r game
        echo "Executable removed."
        exit 0
    fi
fi

mkdir -p game
mkdir -p game/saves

echo "Compiling project..."

cd impl
cmake . 
make --no-print-directory

echo "Removing makefiles..."

rm -rf Makefile CMakeCache.txt  CMakeFiles/ cmake_install.cmake sudoku_autogen/ *.cpp

mv sudoku ../game

echo "Done!"

exit 0;