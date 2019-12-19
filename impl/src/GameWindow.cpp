#include "../inc/GameWindow.hpp"

GameWindow::GameWindow(int difficulty, QWidget *parent): QWidget(parent) {

    layout = new QVBoxLayout();
    bottomLayout = new QHBoxLayout();
    grid = new Grid();
    grid->generate(difficulty);
    gridLayout = generateGridLayout(grid);

    layout->addLayout(gridLayout);
    
    clear_button = new QPushButton("Clear", new QWidget());
    solve_button = new QPushButton("Solve", new QWidget());
    q_button = new QPushButton("Quit", new QWidget());
    
    bottomLayout->addWidget(clear_button);
    bottomLayout->addWidget(solve_button);
    bottomLayout->addWidget(q_button);

    connect(solve_button, SIGNAL(clicked()), this, SLOT(solve()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));

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
            layout->addWidget(new Number(grid->elem(i,j),((i-1)/3+(j-1)/3)%2 ? "#dfdfdf" : "#ffffff"),i,j);
    return layout;
}

Number* GameWindow::cell(int i, int j) {
    return static_cast<Number*>(gridLayout->itemAtPosition(i,j)->widget());
}

void GameWindow::setCell(int i, int j, int data) {
    cell(i,j)->setText(QString(data ? std::to_string(data).c_str() : ""));
    cell(i,j)->setAlignment(Qt::AlignCenter);
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
}
