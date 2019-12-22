#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <QString>
#include <QFont>
#include <QTextCursor>
#include <string>
#include "Grid.hpp"
#include "Number.hpp"

class GameWindow: public QWidget
{
    Q_OBJECT
private:
    QGridLayout *gridLayout;
    QHBoxLayout *bottomLayout;
    QPushButton *clear_button, *solve_button, *back_button, *q_button;
    QVBoxLayout *layout;
    Grid *grid;

    QGridLayout* generateGridLayout(Grid*);
    void setCell(int,int,int);
    Number* cell(int,int);
public:
    explicit GameWindow(int difficulty, QWidget *parent = 0);
    ~GameWindow();
public slots:
    void clear();
    void solve();
    void back();
};

#endif