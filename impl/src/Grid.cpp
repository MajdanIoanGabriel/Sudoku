#include "Grid.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono> 

Grid::Grid() {
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            solvedData[i][j] = 0;

    int row;
    int column;
    int values[] = {1,2,3,4,5,6,7,8,9};

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(values,values+9,std::default_random_engine(seed));

    for(int i=0; i<9; i++) {
        solvedData[0][i] = values[i];
    }

    if(solve(solvedData))
        std::cout<<"Grid succesfully generated"<<std::endl;
    
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            data[i][j] = 0;
}

Grid::Grid(int** d) {
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            data[i][j] = d[i][j];
}

Grid::~Grid() {}

void Grid::printData() {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++)
            std::cout<<data[i][j]<<" ";
        std::cout<<std::endl;
    }
        
}

void Grid::printSolved() {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++)
            std::cout<<solvedData[i][j]<<" ";
        std::cout<<std::endl;
    }
        
}

bool Grid::inRow(int gridData[9][9] , int row, int column, int el) {
    for(int i=0; i<9; i++)
        if(el == gridData [row][i])
            return true;
    return false;
}

bool Grid::inColumn(int gridData[9][9] , int row, int column, int el) {
    for(int i=0; i<9; i++)
        if(el == gridData [i][column])
            return true;
    return false;
}

bool Grid::inSquare(int gridData[9][9] , int row, int column, int el) {
    row = row/3*3;
    column = column/3*3;

    for(int i=row; i<row+3; i++)
        for(int j=column; j<column+3; j++)
            if(el == gridData [i][j])
                return true;
    return false;
}

bool Grid::isValid(int gridData[9][9] , int row, int column, int el) {
    if(inRow(gridData,row,column,el) || inColumn(gridData,row,column,el) || inSquare(gridData,row,column,el))
        return false;
    return true;
}

bool Grid::findEmpty(int gridData[9][9] , int &row, int &column) {
    for(row=0; row<9; row++)
        for(column=0; column<9; column++)
            if(!gridData[row][column])
                return true;
    return false;
}

bool Grid::solve(int gridData[9][9] ) {
    int row;
    int column;

    if(!findEmpty(gridData,row,column))
    return true;

    for(int val=1; val<=9; val++) {
        if(isValid(gridData,row,column,val)) {
            gridData[row][column] = val;
            if(solve(gridData))
                return true;
            gridData[row][column] = 0;
        }

    }

    return false;
}

void Grid::countSolutions(int &number) {
    int row;
    int column;

    if(!findEmpty(data,row,column)) {
        number++;
        return;
    }


    for(int i=0; i<9 && number<2; i++)
    {
        if( isValid(data,row,column,i+1) )
        {
            data[row][column] = i+1;
            countSolutions(number);
        }

        data[row][column] = 0;
    }
}

bool Grid::generate(int difficulty) {
    return true;
    

}