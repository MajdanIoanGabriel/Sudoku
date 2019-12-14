#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QStackedLayout>
#include "MainWindow.h"
#include "GameWindow.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    QWidget parent;
    parent.setFixedSize(600,600);

    //MainWindow Main;
    GameWindow Game;
    QStackedLayout layout;
    //layout.setStackingMode(QStackedLayout::StackAll);
    //layout.addWidget(&Main);
    layout.addWidget(&Game);

    //layout.setCurrentWidget(&Main);

    parent.setLayout(&layout);
    parent.show();

return app.exec();

}