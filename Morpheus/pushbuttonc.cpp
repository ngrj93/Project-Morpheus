#include<pushbuttonc.h>

PushButtonc::PushButtonc(QWidget *parent):QPushButton(parent){

}

void PushButtonc::enable(){
    this->setEnabled(true);
}

void PushButtonc::disable(){
    this->setDisabled(true);
}

