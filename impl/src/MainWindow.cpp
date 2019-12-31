#include "../inc/MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {

    layout = new QGridLayout();
    QVBoxLayout *button_layout = new QVBoxLayout();

    title = new QLabel("SUDOKU");
    title->setStyleSheet("QLabel { font-family: \"Times New Roman\", Times, serif; font-size: 100px; }");

    s_button = new QPushButton("Start");
    q_button = new QPushButton("Quit");

    s_button->setFixedSize(200,30);
    q_button->setFixedSize(200,30);

    button_layout->addWidget(s_button);
    button_layout->addWidget(q_button);

    button_layout->setAlignment(s_button,Qt::AlignHCenter);
    button_layout->setAlignment(q_button,Qt::AlignHCenter);

    layout->addWidget(title,1,2);
    layout->addWidget(new QWidget(),2,1);
    layout->addLayout(button_layout,2,2);
    layout->addWidget(new QWidget(),2,3);
    layout->addWidget(new QWidget(),3,1);
    layout->addWidget(new QWidget(),3,2);
    layout->addWidget(new QWidget(),3,3);

    this->setLayout(layout);

    connect(s_button, SIGNAL(clicked()), this, SLOT(start()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    show();
}

MainWindow::~MainWindow() {}

void MainWindow::start() {
    QStackedWidget *stack = ((QStackedWidget*)parent());
    stack->setCurrentWidget(stack->widget(1));
}
