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
    bool solve();

private:
    int data[9][9];
    int solvedData[9][9];

    bool inRow(int,int,int);
    bool inColumn(int,int,int);
    bool inSquare(int,int,int);
    bool isValid(int,int,int);
    bool findEmpty(int&,int&);
};

#endif