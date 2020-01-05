#include "../inc/GameWindow.hpp"

GameWindow::GameWindow(QWidget *parent): QWidget(parent) {

    layout = new QHBoxLayout();
    rightLayout = new QVBoxLayout();
    username = new QLabel();
    grid = new Grid();

    grid->generate();
    gridLayout = generateGridLayout(grid);

    setStyleSheet("QPushButton { font-family: \"Times New Roman\", Times, serif; font-size: 25px; }");
    username->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 35px; }");


    layout->addLayout(gridLayout);
    
    clear_button = new QPushButton("Clear");
    solve_button = new QPushButton("Solve");
    back_button = new QPushButton("Back");
    q_button = new QPushButton("Quit");

    clear_button->setFixedSize(250,50);
    solve_button->setFixedSize(250,50);
    back_button->setFixedSize(250,50);
    q_button->setFixedSize(250,50);
    
    rightLayout->addWidget(username);
    rightLayout->addWidget(clear_button);
    rightLayout->addWidget(solve_button);
    rightLayout->addWidget(back_button);
    rightLayout->addWidget(q_button);

    rightLayout->setAlignment(username,Qt::AlignTop | Qt::AlignHCenter);

    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));
    connect(solve_button, SIGNAL(clicked()), this, SLOT(solve()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(q_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(back()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    layout->addLayout(rightLayout);
    layout->setAlignment(gridLayout,Qt::AlignTop);
    layout->setAlignment(rightLayout,Qt::AlignHCenter);

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
    cell(i,j)->setText(QString(std::to_string(data).c_str()));
    cell(i,j)->setAlignment(Qt::AlignCenter);
}

Grid* GameWindow::getGrid() {
    return grid;
}

void GameWindow::clear() {
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++)
            if(!(cell(i,j)->isReadOnly())) {
                disconnect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
                setCell(i,j,0);
                connect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
            }     
    validate();    
}

void GameWindow::solve() {
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++) {
            disconnect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
            setCell(i,j,grid->solvedElem(i,j));
            connect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
        }
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
                cell(i,j)->setColor("#ff483b");
            else
                cell(i,j)->setColor(); 
        }
}

void GameWindow::setUserName(QString uname) {
    username->setText(uname);
}

void GameWindow::save() {
    QString filename{username->text()+".txt"};
    QString path{QCoreApplication::applicationDirPath()+"/saves/"};
    QFile savefile{path+filename};
    
    if(savefile.open(QIODevice::ReadWrite)) {
        QTextStream stream(&savefile);
        
        for(int i=1; i<=9; i++) {
            for (int j=1; j<=9; j++) {
                stream << getGrid()->elem(i,j) << getGrid()->solvedElem(i,j);
                if(cell(i,j)->isReadOnly())
                    stream << 1;
                else 
                    stream << 0;
            }
            stream << endl;
        }

        savefile.close();
    }
}

void GameWindow::load() {
    QString filename{username->text()+".txt"}, path{QCoreApplication::applicationDirPath()+"/saves/"};
    QFile savefile{path+filename};
    
    if(savefile.open(QIODevice::ReadWrite)) {
        int loadedData[3][9][9];
        for(int i=0; i<9; i++) {
            QString line = savefile.readLine();
            for (int j=0; j<9; j++) {
                loadedData[0][i][j] = line[3*j].digitValue();
                loadedData[1][i][j] = line[3*j+1].digitValue();
                loadedData[2][i][j] = line[3*j+2].digitValue();
            }
        }

        grid = new Grid(loadedData);

        for(int i=1; i<=9; i++)
            for(int j=1; j<=9; j++) {
                disconnect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
                setCell(i,j,loadedData[0][i-1][j-1]);
                if(loadedData[2][i-1][j-1])
                    cell(i,j)->setReadOnly(true);
                cell(i,j)->setColor();
                connect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
        }

        validate();
        savefile.close();
    }
}

void GameWindow::newGame() {
    grid = new Grid();
    int difficulty{(static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getDifficulty()};

    grid->generate(difficulty);

    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++) {
            disconnect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
            setCell(i,j,grid->elem(i,j));
            if((cell(i,j)->value()))
                cell(i,j)->setReadOnly(true);
            else
                cell(i,j)->setReadOnly(false);
            cell(i,j)->setColor();
            connect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
        }

}
