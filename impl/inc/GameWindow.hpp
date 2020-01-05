#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <iostream>
#include <QFile>
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
#include <QLabel>
#include <QTextStream>
#include <QTimer>
#include <QTime>
#include <string>
#include "MainWindow.hpp"
#include "Grid.hpp"
#include "Number.hpp"

class Number;
class GameWindow: public QWidget
{
    Q_OBJECT
private:
    QGridLayout *gridLayout;
    QVBoxLayout *rightLayout;
    QLabel *username, *timeLabel;
    QPushButton *clear_button, *solve_button, *back_button, *q_button;
    QHBoxLayout *layout;
    Grid *grid;
    QTimer *timer;
    QTime *time;

    QGridLayout* generateGridLayout(Grid*);
    void setCell(int,int,int);
    Number* cell(int,int);
    bool inRow(int,int);
    bool inColumn(int,int);
    bool inSquare(int,int);
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    Grid* getGrid();
    void setUserName(QString);
public slots:
    void clear();
    void solve();
    void back();
    void validate();
    void save();
    void load();
    void newGame();
    void count();
};

#endif