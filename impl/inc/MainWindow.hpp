#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "GameWindow.hpp"


class MainWindow: public QWidget
{
    Q_OBJECT
private:
    QLabel *title, *welcome, *difficulty;
    QLineEdit *username;
    QRadioButton *easy, *medium, *hard, *insane;
    QPushButton *c_button, *n_button, *q_button;
    QGridLayout *layout;
public:
    explicit MainWindow(QWidget *parent = 0);
    void init();
    ~MainWindow();
    int getDifficulty();
    QPushButton* getCButton();
public slots:
    void start();
    void continueGame();
};

#endif