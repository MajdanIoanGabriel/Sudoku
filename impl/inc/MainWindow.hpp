#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QPushButton>
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
    QLabel *title, *welcome;
    QLineEdit *username;
    QPushButton *c_button, *n_button, *q_button;
    QGridLayout *layout;
public:
    explicit MainWindow(QWidget *parent = 0);
    void init();
    ~MainWindow();
public slots:
    void start();
};

#endif