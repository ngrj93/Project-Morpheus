#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QThread>
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void write(QString s);
    void init();
    void reset();
    
private slots:
    void on_pushButton_3_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_7_valueChanged(int arg1);
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_horizontalSlider_2_valueChanged(int value);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_spinBox_8_valueChanged(int arg1);
    void on_spinBox_6_valueChanged(int arg1);
    void on_spinBox_5_valueChanged(int arg1);
    void on_spinBox_4_valueChanged(int arg1);
    void on_spinBox_3_valueChanged(int arg1);
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();


private:
    Ui::MainWindow *ui;
    QThread *thread;
    Worker *worker;
};

#endif // MAINWINDOW_H
