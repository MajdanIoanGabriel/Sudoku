#include <iostream>
#include "Grid.hpp"

int main() {
    
    Grid sudoku;
    int difficulty;
    std::cout<<"Solved sudoku grid:\n";
    sudoku.printSolved();

    std::cout<<"Sudoku on easy difficulty:\n";
    sudoku.generate(1);
    sudoku.printData();
    
    std::cout<<"Sudoku on medium difficulty:\n";
    sudoku.generate(2);
    sudoku.printData();

    std::cout<<"Sudoku on hard difficulty:\n";
    sudoku.generate(3);
    sudoku.printData();

    std::cout<<"Sudoku on insane difficulty:\n";
    sudoku.generate(4);
    sudoku.printData();
    
    
    return 0;
}