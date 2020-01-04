#include "../inc/MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {

    layout = new QGridLayout();
    QVBoxLayout *button_layout = new QVBoxLayout();
    QVBoxLayout *login_layout = new QVBoxLayout();

    title = new QLabel("SUDOKU");
    welcome = new QLabel("Welcome");
    username = new QLineEdit("Guest");

    title->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 100px; }");
    username->setAlignment(Qt::AlignHCenter);

    c_button = new QPushButton("Continue");
    n_button = new QPushButton("New Game");
    q_button = new QPushButton("Quit");

    c_button->setFixedSize(200,30);
    n_button->setFixedSize(200,30);
    q_button->setFixedSize(200,30);

    button_layout->addWidget(c_button);
    button_layout->addWidget(n_button);
    button_layout->addWidget(q_button);

    button_layout->setAlignment(c_button,Qt::AlignHCenter);
    button_layout->setAlignment(n_button,Qt::AlignHCenter);
    button_layout->setAlignment(q_button,Qt::AlignHCenter);

    login_layout->addWidget(welcome);
    login_layout->addWidget(username);

    login_layout->setAlignment(welcome,Qt::AlignHCenter);
    login_layout->setAlignment(username,Qt::AlignHCenter);

    layout->addWidget(title,1,2);
    layout->addLayout(login_layout,2,1);
    layout->addLayout(button_layout,2,2);
    layout->addWidget(new QWidget(),2,3);
    layout->addWidget(new QWidget(),3,1);
    layout->addWidget(new QWidget(),3,2);
    layout->addWidget(new QWidget(),3,3);

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
    stack->setCurrentWidget(stack->widget(1));

    (static_cast<GameWindow*>(stack->widget(1)))->setUserName(username->text());
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
        c_button->setStyleSheet("QPushButton { background-color: #999999; }");
    }
}
