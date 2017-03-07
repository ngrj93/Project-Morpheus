#ifndef SPINBOXC_H
#define SPINBOXC_H

#include<QSpinBox>

class SpinBoxc : public QSpinBox
{
    Q_OBJECT
public:
    SpinBoxc(QWidget *parent = 0);
private slots:
    void disable();
    void enable();
};

#endif // SPINBOXC_H
