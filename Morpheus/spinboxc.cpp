#include <spinboxc.h>

SpinBoxc::SpinBoxc(QWidget *parent):QSpinBox(parent)
{

}

void SpinBoxc::disable(){
    this->setDisabled(true);
}

void SpinBoxc::enable(){
    this->setEnabled(true);
}
