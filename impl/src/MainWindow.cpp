#include "../inc/MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {

    layout = new QGridLayout();
    QVBoxLayout *button_layout = new QVBoxLayout();
    QVBoxLayout *login_layout = new QVBoxLayout();
    QVBoxLayout *difficulty_layout = new QVBoxLayout();

    title = new QLabel("SUDOKU");
    welcome = new QLabel("Welcome");
    username = new QLineEdit("Guest");
    difficulty = new QLabel("Difficulty \n(for new game): ");

    title->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 100px; }");
    username->setAlignment(Qt::AlignHCenter);
    welcome->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 25px; }");
    difficulty->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 25px; }");
    username->setStyleSheet("QLineEdit { font-family: \"Times New Roman\", Times, serif; font-size: 25px; }");
    setStyleSheet("QPushButton, QRadioButton { font-family: \"Times New Roman\", Times, serif; font-size: 25px; } QRadioutton { border: none }");

    c_button = new QPushButton("Continue");
    n_button = new QPushButton("New Game");
    q_button = new QPushButton("Quit");

    c_button->setFixedSize(250,50);
    n_button->setFixedSize(250,50);
    q_button->setFixedSize(250,50);

    button_layout->addWidget(c_button);
    button_layout->addWidget(n_button);
    button_layout->addWidget(q_button);

    login_layout->addWidget(welcome);
    login_layout->addWidget(username);

    login_layout->setAlignment(welcome,Qt::AlignHCenter);
    login_layout->setAlignment(username,Qt::AlignHCenter);

    easy = new QRadioButton("Easy");
    medium = new QRadioButton("Medium");
    hard = new QRadioButton("Hard");
    insane = new QRadioButton("Insane");
    easy->setChecked(true);

    difficulty_layout->addWidget(difficulty);
    difficulty_layout->addWidget(easy);
    difficulty_layout->addWidget(medium);
    difficulty_layout->addWidget(hard);
    difficulty_layout->addWidget(insane);

    

    layout->addWidget(title,1,2);
    layout->addLayout(login_layout,2,1);
    layout->addLayout(button_layout,2,2);
    layout->addLayout(difficulty_layout,2,3);
    layout->addWidget(new QWidget(),3,1);
    layout->addWidget(new QWidget(),3,2);
    layout->addWidget(new QWidget(),3,3);

    layout->setAlignment(login_layout,Qt::AlignTop);
    layout->setAlignment(button_layout,Qt::AlignHCenter);
    layout->setAlignment(difficulty_layout,Qt::AlignHCenter);

    this->setLayout(layout);

    show();
}

void MainWindow::init() {
    GameWindow* gameWindow = static_cast<GameWindow*>(((QStackedWidget*)parent())->widget(1));

    connect(username, SIGNAL(returnPressed()), this, SLOT(continueGame()));
    connect(n_button, SIGNAL(clicked()), this, SLOT(start()));
    connect(n_button, SIGNAL(clicked()), gameWindow, SLOT(newGame()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    continueGame();
}

MainWindow::~MainWindow() {}

void MainWindow::start() {
    QStackedWidget *stack = ((QStackedWidget*)parent());
    GameWindow* gameWindow = static_cast<GameWindow*>(stack->widget(1));
    stack->setCurrentWidget(gameWindow);

    gameWindow->setUserName(username->text());
}

void MainWindow::continueGame() {
    QString filename{username->text()+".txt"};
    QString path{QCoreApplication::applicationDirPath()+"/saves/"};
    GameWindow* gameWindow = static_cast<GameWindow*>(((QStackedWidget*)parent())->widget(1));

    if(QFile::exists(path+filename)) {
        connect(c_button, SIGNAL(clicked()), this, SLOT(start()));
        connect(c_button, SIGNAL(clicked()), gameWindow, SLOT(load()));
        c_button->setStyleSheet("");
    }
    else {
        disconnect(c_button, SIGNAL(clicked()), this, SLOT(start()));
        disconnect(c_button, SIGNAL(clicked()), gameWindow, SLOT(load()));
        c_button->setStyleSheet("QPushButton { background-color: #DDDDDD; }");
    }
}

int MainWindow::getDifficulty() {
    QRadioButton* buttons[]{easy,medium,hard,insane};
    for(int i=0; i<4; i++) {
        if(buttons[i]->isChecked())
            return i+1;
    }
    return 2;
}

QPushButton* MainWindow::getCButton() {
    return c_button;
}
