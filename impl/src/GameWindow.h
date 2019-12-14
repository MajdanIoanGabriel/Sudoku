#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <QString>
#include <QFont>
#include <QTextCursor>
#include <string>

class GameWindow: public QWidget
{
private:
    QGridLayout *gridLayout;
    QPushButton *q_button;
    QVBoxLayout *layout;

    QTextEdit* Number(std::string color, int n);
    QGridLayout* generateGridLayout();
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
};

#endif