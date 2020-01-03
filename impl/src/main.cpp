#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include "../inc/MainWindow.hpp"
#include "../inc/GameWindow.hpp"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    QStackedWidget *parent = new QStackedWidget();
    parent->setFixedSize(800,600);

    
    MainWindow Main(parent);
    GameWindow Game(parent);

    parent->addWidget(&Main);
    parent->addWidget(&Game);

    Main.init();

    parent->setCurrentWidget(&Main);

    parent->show();

return app.exec();

}