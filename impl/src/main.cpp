#include <iostream>
#include "Grid.hpp"

int main() {
    
    Grid sudoku;
    int difficulty;
    sudoku.printSolved();
    
    std::cout<<"\nPlease enter dificulty: \n"
        <<"1. Easy \n"
        <<"2. Medium \n"
        <<"3. Hard \n";
    std::cin>>difficulty;

    if(sudoku.generate(difficulty))
        sudoku.printData();
    
    return 0;
}