#ifndef PUSHBUTTONC_H
#define PUSHBUTTONC_H

#include<QPushButton>

class PushButtonc: public QPushButton{
    Q_OBJECT
public:
    PushButtonc(QWidget *parent=0);
private slots:
    void enable();
    void disable();
};

#endif // PUSHBUTTONC_H
