#include "../inc/GameWindow.hpp"

GameWindow::GameWindow(int difficulty, QWidget *parent): QWidget(parent) {

    layout = new QVBoxLayout();
    bottomLayout = new QHBoxLayout();
    grid = new Grid();
    grid->generate(difficulty);
    gridLayout = generateGridLayout(grid);

    layout->addLayout(gridLayout);
    
    clear_button = new QPushButton("Clear");
    solve_button = new QPushButton("Solve");
    back_button = new QPushButton("Back");
    q_button = new QPushButton("Quit");
    
    bottomLayout->addWidget(clear_button);
    bottomLayout->addWidget(solve_button);
    bottomLayout->addWidget(back_button);
    bottomLayout->addWidget(q_button);

    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));
    connect(solve_button, SIGNAL(clicked()), this, SLOT(solve()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(back()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    layout->addLayout(bottomLayout);
    layout->setAlignment(gridLayout,Qt::AlignTop);

    this->setLayout(layout);

    show();
}

GameWindow::~GameWindow() {}

QGridLayout* GameWindow::generateGridLayout(Grid *grid) {
    QGridLayout *layout = new QGridLayout();
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++)
            layout->addWidget(new Number(grid->elem(i,j),i,j,((i-1)/3+(j-1)/3)%2 ? "#dfdfdf" : "#ffffff", this),i,j);
    return layout;
}

Number* GameWindow::cell(int i, int j) {
    return static_cast<Number*>(gridLayout->itemAtPosition(i,j)->widget());
}

void GameWindow::setCell(int i, int j, int data) {
    cell(i,j)->setText(QString(data ? std::to_string(data).c_str() : ""));
    cell(i,j)->setAlignment(Qt::AlignCenter);
}

Grid* GameWindow::getGrid() {
    return grid;
}

void GameWindow::clear() {
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++)
            if(!grid->elem(i,j))
                setCell(i,j,0);
}

void GameWindow::solve() {
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++)
            setCell(i,j,grid->solvedElem(i,j));
    validate();
}

void GameWindow::back() {
    ((QStackedWidget*)parent())->setCurrentWidget(((QStackedWidget*)parent())->widget(0));
}

bool GameWindow::inRow(int x, int y) {
    for(int j=1; j<=9; j++) {
        if(y == j)
            continue;
        if(cell(x,y)->value() == getGrid()->elem(x,j))
            return true;
    }  
    return false;
}

bool GameWindow::inColumn(int x, int y) {
    for(int i=1; i<=9; i++) {
        if(x == i)
            continue;
        if(cell(x,y)->value() == getGrid()->elem(i,y))
            return true;
    }
    return false;
}

bool GameWindow::inSquare(int x, int y) {
    int row = (x-1)/3*3;
    int column = (y-1)/3*3;

    for(int i=row+1; i<=row+3; i++)
        for(int j=column+1; j<=column+3; j++) {
            if(x == i && y == j)
                continue;
            if(cell(x,y)->value() == getGrid()->elem(i,j))
                return true;
        }
    return false;
}

void GameWindow::validate() {
    for(int i=1; i<=9; i++) 
        for(int j=1; j<=9; j++) {
            if((inRow(i,j) || inColumn(i,j) || inSquare(i,j)) && !(cell(i,j)->value() == 0))
                cell(i,j)->setColor("red");
            else
                cell(i,j)->setColor(); 
        }
}
