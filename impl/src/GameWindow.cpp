#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent): QWidget(parent) {
    //setFixedSize(400,400);

    layout = new QVBoxLayout();
    gridLayout = generateGridLayout();

    layout->addLayout(gridLayout);

    q_button = new QPushButton("Quit", new QWidget());
    q_button->setGeometry(0, 0, 80, 30);
    layout->addWidget(q_button);
    layout->setAlignment(q_button,Qt::AlignBottom);

    this->setLayout(layout);

    connect(q_button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    show();
}

GameWindow::~GameWindow() {}

QTextEdit* GameWindow::Number(std::string color, int n=0) {
    QTextEdit *elem = new QTextEdit();
    if(n)
        elem->setText(QString(std::to_string(n).c_str()));
    elem->setReadOnly(true);
    elem->setAlignment(Qt::AlignCenter);

    QTextCursor cursor = elem->textCursor();
    elem->selectAll();
    elem->setFontPointSize(20);
    elem->setTextCursor(cursor);

    elem->setStyleSheet(("QTextEdit { background-color: "+color+"; }").c_str());
    return elem;
}

QGridLayout* GameWindow::generateGridLayout() {
    QGridLayout *grid = new QGridLayout();
    for(int i=1; i<=9; i+=3)
        for(int j=1; j<=9; j+=3)
            for(int k=i; k<i+3; k++)
                for(int l=j; l<j+3; l++)
                    if((i+j)%2)
                        grid->addWidget(Number("#ebebeb"),k,l);
                    else
                        grid->addWidget(Number("#b8b8b8"),k,l);
    return grid;
}
