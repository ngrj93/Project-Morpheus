#include<horizontalsliderc.h>

HorizontalSliderc::HorizontalSliderc(QWidget *parent):QSlider(parent){

}

void HorizontalSliderc::enable(){
    this->setEnabled(true);
}

void HorizontalSliderc::disable(){
    this->setDisabled(true);
}

