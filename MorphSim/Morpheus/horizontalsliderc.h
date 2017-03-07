#ifndef HORIZONTALSLIDERC_H
#define HORIZONTALSLIDERC_H

#include<QSlider>

class HorizontalSliderc:public QSlider{
Q_OBJECT
public:
    HorizontalSliderc(QWidget *parent=0);
private slots:
    void disable();
    void enable();
};

#endif // HORIZONTALSLIDERC_H
