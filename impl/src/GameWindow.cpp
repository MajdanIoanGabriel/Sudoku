#include "../inc/GameWindow.hpp"

GameWindow::GameWindow(QWidget *parent): QWidget(parent) {

    layout = new QHBoxLayout();
    rightLayout = new QVBoxLayout();
    username = new QLabel();
    timeLabel = new QLabel();
    grid = new Grid();
    timer = new QTimer(this);
    time = new QTime(0,0);
    emptyPos = 81;

    grid->generate();
    gridLayout = generateGridLayout(grid);

    setStyleSheet("QPushButton { font-family: \"Times New Roman\", Times, serif; font-size: 25px; }");
    username->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 35px; }");
    timeLabel->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 35px; }");


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
    rightLayout->addWidget(timeLabel);
    rightLayout->addWidget(clear_button);
    rightLayout->addWidget(solve_button);
    rightLayout->addWidget(back_button);
    rightLayout->addWidget(q_button);

    rightLayout->setAlignment(username,Qt::AlignTop | Qt::AlignHCenter);
    rightLayout->setAlignment(timeLabel,Qt::AlignTop | Qt::AlignHCenter);

    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));
    connect(solve_button, SIGNAL(clicked()), this, SLOT(solve()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(q_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(back()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(timer, SIGNAL(timeout()), this, SLOT(count()));

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
    QString filename{username->text()+".txt"}, path{QCoreApplication::applicationDirPath()+"/saves/"};
    QFile savefile{path+filename};
    savefile.remove();
}

void GameWindow::back() {
    ((QStackedWidget*)parent())->setCurrentWidget(((QStackedWidget*)parent())->widget(0));
    timer->stop();
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

    if(!grid->countEmptyPos()) {
        for(int i=1; i<=9; i++)
            for(int j=1; j<=9; j++)
                if(cell(i,j)->value() != grid->solvedElem(i,j))
                    return;
        for(int i=1; i<=9; i++)
            for(int j=1; j<=9; j++)
                cell(i,j)->setColor("#84e36f");
        timeLabel->setText("Congratulations\n"+timeLabel->text());
        disconnect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));
        disconnect(solve_button, SIGNAL(clicked()), this, SLOT(solve()));
        disconnect((static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getCButton(), SIGNAL(clicked()), (static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0))), SLOT(start()));
        disconnect((static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getCButton(), SIGNAL(clicked()), this, SLOT(load()));
        (static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getCButton()->setStyleSheet("QPushButton { background-color: #DDDDDD; }");
        timer->stop();
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

        stream << time->toString() << endl;
        
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
        timeLabel->setText(savefile.readLine());
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
        emptyPos = grid->countEmptyPos(loadedData[0]);

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

        int hour{timeLabel->text()[0].digitValue()*10+timeLabel->text()[1].digitValue()};
        int minute{timeLabel->text()[3].digitValue()*10+timeLabel->text()[4].digitValue()};
        int second{timeLabel->text()[6].digitValue()*10+timeLabel->text()[7].digitValue()};
        time->setHMS(hour, minute, second);
        timer->start(1000);
    }
}

void GameWindow::newGame() {
    grid = new Grid();
    emptyPos = 81;
    int difficulty{(static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getDifficulty()};

    timeLabel->setText("00:00:00");
    time->setHMS(0,0,0);

    grid->generate(difficulty);

    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++) {
            disconnect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
            setCell(i,j,grid->elem(i,j));
            if((cell(i,j)->value()))
                cell(i,j)->setReadOnly(true);
            else {
                cell(i,j)->setReadOnly(false);
                emptyPos--;
            }  
            cell(i,j)->setColor();
            connect(cell(i,j), SIGNAL(textChanged()), this, SLOT(validate()));
        }

    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));
    connect(solve_button, SIGNAL(clicked()), this, SLOT(solve()));

    connect((static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getCButton(), SIGNAL(clicked()), (static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0))), SLOT(start()));
    connect((static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getCButton(), SIGNAL(clicked()), this, SLOT(load()));
    (static_cast<MainWindow*>(((QStackedWidget*)parent())->widget(0)))->getCButton()->setStyleSheet("");
    timer->start(1000);
}

void GameWindow::count() {
    *time = time->addSecs(1);
    timeLabel->setText(time->toString());
}

void GameWindow::addEmptyPos(int nr) {
    emptyPos += nr;
}
