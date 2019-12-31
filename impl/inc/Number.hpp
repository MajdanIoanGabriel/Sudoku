#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <QTextEdit>
#include <QFrame>
#include <QString>
#include "GameWindow.hpp"
#include <string>

class Number: public QTextEdit
{
    Q_OBJECT
private:
    static Number* selected;
    std::string color;
    int x, y;
public:
    explicit Number(int n, int x, int y, std::string color, QWidget *parent = 0);
    ~Number();
    void setColor(std::string color = "");
    int value();
public slots:
    void validate();
    void focus();
};


#endif
