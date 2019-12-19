#include "../inc/Number.hpp"

Number* Number::selected;

Number::Number(int n, std::string color, QTextEdit *parent): QTextEdit(parent) {
    setStyleSheet(("QTextEdit { background-color: "+color+"; font-size: 33px; color: "+(n==0 ? "#999999" : "#000000")+"}").c_str());
    
    if(n) {
        setText(QString(std::to_string(n).c_str()));
        setReadOnly(true);
    }

    setCursorWidth(0);
    setAlignment(Qt::AlignCenter);
    setFrameShape(QFrame::Box);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    connect(this, SIGNAL(textChanged()), this, SLOT(validate()));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(focus()));

}

Number::~Number() {}

void Number::validate() {
    QString text = toPlainText();
    if(text.length() > 1) {
        text.chop(text.length()-1);
    }

    if(!text[0].isDigit() || text == "0")
        text = " ";

    if(toPlainText() != text) {
        setText(text);
        setAlignment(Qt::AlignCenter);
    }
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
