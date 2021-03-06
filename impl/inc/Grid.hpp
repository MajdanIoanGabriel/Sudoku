#ifndef GRID_HPP
#define GRID_HPP

class Grid
{
public:
    Grid();
    Grid(int[3][9][9]);
    ~Grid();

    void generate(int difficulty = 0);
    bool solve(int[9][9]);
    void countSolutions(int&);
    int countEmptyPos(int[9][9] = 0);
    int elem(int,int);
    void setElem(int,int,int);
    int solvedElem(int,int);

private:
    int data[9][9];
    int solvedData[9][9];
    int gridPos[81];

    bool inRow(int[9][9],int,int,int);
    bool inColumn(int[9][9],int,int,int);
    bool inSquare(int[9][9],int,int,int);
    bool isValid(int[9][9],int,int,int);
    bool findEmpty(int[9][9],int&,int&);
};

#endif