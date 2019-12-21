#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include "../inc/MainWindow.hpp"
#include "../inc/GameWindow.hpp"

void usage() {
    std::cout<<"In order to generate a new game, run:\n"
    <<"./sudoku [dificulty]\n"
    <<"where difficulty:\n"
    <<"1 - easy\n"
    <<"2 - normal\n"
    <<"3 - hard\n"
    <<"4 - insane\n";
    exit(1);
}

void verify(char* diff_arg) {
    if(!diff_arg)
        usage();
    std::string difficulty{diff_arg};
    if(difficulty.length() != 1)
        usage();
    else if(difficulty[0] < '1' || difficulty[0] > '4')
            usage();
}

int main(int argc, char **argv)
{
    verify(argv[1]);
    std::string difficulty{argv[1]};

    QApplication app (argc, argv);
    QStackedWidget *parent = new QStackedWidget();
    parent->setFixedSize(600,600);

    
    MainWindow Main(parent);
    GameWindow Game(stoi(difficulty),parent);

    parent->addWidget(&Main);
    parent->addWidget(&Game);

    parent->setCurrentWidget(&Main);

    parent->show();

return app.exec();

}