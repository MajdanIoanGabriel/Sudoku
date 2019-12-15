#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    setFixedSize(400,400);

    layout = new QVBoxLayout();

    s_button = new QPushButton("Start", new QWidget());
    s_button->setGeometry(0, 0, 80, 30);
    layout->addWidget(s_button);
    layout->setAlignment(s_button,Qt::AlignBottom);

    q_button = new QPushButton("Quit", new QWidget());
    q_button->setGeometry(0, 0, 80, 30);
    layout->addWidget(q_button);
    layout->setAlignment(q_button,Qt::AlignTop);

    this->setLayout(layout);

    connect(s_button, SIGNAL(clicked()), this, SLOT(hide()));
    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    show();
}

MainWindow::~MainWindow()
{
}
