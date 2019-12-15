#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent): QWidget(parent) {

    layout = new QVBoxLayout();
    bottomLayout = new QHBoxLayout();
    grid = new Grid();
    grid->generate(2);
    gridLayout = generateGridLayout(grid);

    layout->addLayout(gridLayout);
    
    clear_button = new QPushButton("Clear", new QWidget());
    solve_button = new QPushButton("Solve", new QWidget());
    q_button = new QPushButton("Quit", new QWidget());
    
    bottomLayout->addWidget(clear_button);
    bottomLayout->addWidget(solve_button);
    bottomLayout->addWidget(q_button);

    layout->addLayout(bottomLayout);
    layout->setAlignment(gridLayout,Qt::AlignTop);

    this->setLayout(layout);

    connect(solve_button, SIGNAL(clicked()), this, SLOT(solve()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));

    show();
}

GameWindow::~GameWindow() {}

QTextEdit* GameWindow::Number(std::string color, int n=0) {
    QTextEdit *elem = new QTextEdit();

    elem->setStyleSheet(("QTextEdit { background-color: "+color+"; font-size: 33px; color: "+(n==0 ? "#999999" : "#000000")+"}").c_str());
    

    if(n) {
        elem->setText(QString(std::to_string(n).c_str()));
        elem->setReadOnly(true);
    }

    elem->setAlignment(Qt::AlignCenter);

    return elem;
}

QGridLayout* GameWindow::generateGridLayout(Grid *grid) {
    QGridLayout *layout = new QGridLayout();
    for(int i=1; i<=9; i+=3)
        for(int j=1; j<=9; j+=3)
            for(int k=i; k<i+3; k++)
                for(int l=j; l<j+3; l++)
                        layout->addWidget(Number((i+j)%2 ? "#dfdfdf" : "#ffffff",grid->elem(k,l)),k,l);
    return layout;
}

void GameWindow::setCell(int i, int j, int data) {
    static_cast<QTextEdit*>(gridLayout->itemAtPosition(i,j)->widget())->setText(QString(data ? std::to_string(data).c_str() : ""));
    static_cast<QTextEdit*>(gridLayout->itemAtPosition(i,j)->widget())->setAlignment(Qt::AlignCenter);
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
