#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>


class MainWindow: public QWidget
{
private:
    QPushButton *s_button, *q_button;
    QVBoxLayout *layout;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif