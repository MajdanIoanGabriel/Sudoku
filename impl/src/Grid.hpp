#ifndef GRID_HPP
#define GRID_HPP

class Grid
{
public:
    Grid();
    Grid(int**);
    ~Grid();

    void printData();
    void printSolved();
    bool generate(int);
    bool solve(int[9][9]);

private:
    int data[9][9];
    int solvedData[9][9];

    bool inRow(int[9][9],int,int,int);
    bool inColumn(int[9][9],int,int,int);
    bool inSquare(int[9][9],int,int,int);
    bool isValid(int[9][9],int,int,int);
    bool findEmpty(int[9][9],int&,int&);
};

#endif