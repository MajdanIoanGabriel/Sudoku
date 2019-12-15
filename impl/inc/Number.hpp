#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <QTextEdit>
#include <QFrame>
#include <QString>

class Number: public QTextEdit
{
    Q_OBJECT
private:
    static Number* selected;
public:
    explicit Number(int n, std::string color, QTextEdit *parent = 0);
    ~Number();
public slots:
    void validate();
    void focus();
};


#endif
