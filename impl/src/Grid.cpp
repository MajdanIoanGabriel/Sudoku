#include "Grid.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono> 

Grid::Grid() {
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

void Grid::print() {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++)
            std::cout<<data[i][j]<<" ";
        std::cout<<std::endl;
    }
        
}

bool Grid::inRow(int row, int column, int el) {
    for(int i=0; i<9; i++)
        if(el == data[row][i])
            return true;
    return false;
}

bool Grid::inColumn(int row, int column, int el) {
    for(int i=0; i<9; i++)
        if(el == data[i][column])
            return true;
    return false;
}

bool Grid::inSquare(int row, int column, int el) {
    row = row/3*3;
    column = column/3*3;

    for(int i=row; i<row+3; i++)
        for(int j=column; j<column+3; j++)
            if(el == data[i][j])
                return true;
    return false;
}

bool Grid::isValid(int row, int column, int el) {
    if(inRow(row,column,el) || inColumn(row,column,el) || inSquare(row,column,el))
        return false;
    return true;
}

bool Grid::findEmpty(int &row, int &column) {
    for(row=0; row<9; row++)
        for(column=0; column<9; column++)
            if(!data[row][column])
                return true;
    return false;
}

bool Grid::solve() {
    int row;
    int column;

    if(!findEmpty(row,column))
    return true;

    for(int val=1; val<=9; val++) {
        if(isValid(row,column,val)) {
            data[row][column] = val;
            if(solve())
                return true;
            data[row][column] = 0;
        }

    }

    return false;
}

bool Grid::generate(int difficulty) {
    int row;
    int column;
    int values[] = {1,2,3,4,5,6,7,8,9};

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(values,values+9,std::default_random_engine(seed));

    for(int i=0; i<9; i++) {
        data[0][i] = values[i];
    }

    if(solve())
        std::cout<<"Grid succesfully generated"<<std::endl;
    

}