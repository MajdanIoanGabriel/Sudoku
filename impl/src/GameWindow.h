#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <QString>
#include <QFont>
#include <QTextCursor>
#include <string>
#include "Grid.hpp"

class GameWindow: public QWidget
{
    Q_OBJECT
private:
    QGridLayout *gridLayout;
    QHBoxLayout *bottomLayout;
    QPushButton *clear_button, *solve_button, *q_button;
    QVBoxLayout *layout;
    Grid *grid;

    QTextEdit* Number(std::string color, int n);
    QGridLayout* generateGridLayout(Grid*);
    void setCell(int,int,int);
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
public slots:
    void clear();
    void solve();
};

#endif