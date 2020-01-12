#include "../inc/Number.hpp"

Number* Number::selected;

Number::Number(int n, int x, int y, std::string color, QWidget *parent): QTextEdit(parent) {
    this->color = color;
    this->x = x;
    this->y = y;
    setStyleSheet(("Number { background-color: "+color+"; font-size: 33px; color: "+(n==0 ? "#999999" : "#000000")+"} font-family: \"Times New Roman\", Times, serif; ").c_str());
    setFixedSize(60,60);

    if(n) {
        setText(QString(std::to_string(n).c_str()));
        setReadOnly(true);
    }

    setCursorWidth(0);
    setAlignment(Qt::AlignCenter);
    setFrameShape(QFrame::Box);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    connect(this, SIGNAL(selectionChanged()), this, SLOT(focus()));
    connect(this, SIGNAL(textChanged()), this, SLOT(validate()));
    connect(this, SIGNAL(textChanged()), static_cast<GameWindow*>(parent), SLOT(validate()));

}

Number::~Number() {}

void Number::validate() {
    QString text = toPlainText();
    if(text.length() > 1) {
        text.chop(text.length()-1);
    }

    if(!text[0].isDigit() || text == "0") 
        text = "";

    if(toPlainText() != text) {
        setText(text);
        setAlignment(Qt::AlignCenter);
    }

    (static_cast<GameWindow*>(parent()))->getGrid()->setElem(value(),x,y);    
} 

void Number::setColor(std::string color) {
    setStyleSheet(("Number { background-color: "+( color == "" ? this->color : color )+"; font-size: 33px; color: "+(isReadOnly() ? "#000000" : "#999999")+"; font-family: \"Times New Roman\", Times, serif;} ").c_str());
}

void Number::focus() {
    if(selected)
        selected->setLineWidth(1);
    if(isReadOnly()) {
        selected = nullptr;
        return;
    }
    setLineWidth(2);
    selected = this;
}

int Number::value() {
    if(toPlainText().toStdString() == "")
        return 0;
    return std::stoi(toPlainText().toStdString());
}