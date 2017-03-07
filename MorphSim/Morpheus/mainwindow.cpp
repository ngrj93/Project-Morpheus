#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <globshare.h>
#include <QtGui>

volatile int jobs,num,qlength,sn,pn,nn,en,loss,burst_size,plus_node,minus_node,minus_job,plus_job;
volatile char burst;
volatile char state;
QMutex m1,m2;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread=new QThread();
    worker=new Worker();
    worker->moveToThread(thread);
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    connect(ui->radioButton,SIGNAL(clicked()),ui->spinBox_6,SLOT(disable()));
    connect(ui->radioButton,SIGNAL(clicked()),ui->spinBox_4,SLOT(disable()));
    connect(ui->radioButton,SIGNAL(clicked()),ui->spinBox_5,SLOT(disable()));
    connect(ui->radioButton,SIGNAL(clicked()),ui->spinBox_3,SLOT(disable()));
    connect(ui->radioButton,SIGNAL(clicked()),ui->spinBox_8,SLOT(enable()));
    connect(ui->radioButton_2,SIGNAL(clicked()),ui->spinBox_6,SLOT(enable()));
    connect(ui->radioButton_2,SIGNAL(clicked()),ui->spinBox_4,SLOT(enable()));
    connect(ui->radioButton_2,SIGNAL(clicked()),ui->spinBox_5,SLOT(enable()));
    connect(ui->radioButton_2,SIGNAL(clicked()),ui->spinBox_3,SLOT(enable()));
    connect(ui->radioButton_2,SIGNAL(clicked()),ui->spinBox_8,SLOT(disable()));
    connect(ui->radioButton_3,SIGNAL(clicked()),ui->horizontalSlider_2,SLOT(disable()));
    connect(ui->radioButton_4,SIGNAL(clicked()),ui->horizontalSlider_2,SLOT(enable()));
    connect(ui->pushButton,SIGNAL(clicked()),ui->pushButton_2,SLOT(enable()));
    connect(ui->pushButton,SIGNAL(clicked()),ui->pushButton,SLOT(disable()));
    connect(ui->pushButton_2,SIGNAL(clicked()),ui->pushButton,SLOT(enable()));
    connect(ui->pushButton_2,SIGNAL(clicked()),ui->pushButton_2,SLOT(disable()));
    ui->simres->append("<h2>Simulation Result Analysis</h2>");
    worker->setUi(ui);
    init();
}

MainWindow::~MainWindow()
{
    worker->abort();
    thread->wait();
    delete thread;
    delete worker;
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    jobs=arg1;
}

void MainWindow::init(){
     jobs=ui->spinBox->value();
     qlength=ui->spinBox_7->value();
     burst='r';
     state='r';
     num=ui->spinBox_8->value();
     loss=ui->horizontalSlider->value();
     en=nn=0;
     pn=sn=1;
     burst_size=1;
     plus_job=minus_job=plus_node=minus_node=0;
}

void MainWindow::reset(){
    ui->spinBox->setValue(1);
    ui->spinBox->setDisabled(false);
    ui->spinBox_7->setValue(2);
    ui->spinBox_7->setDisabled(false);
    ui->spinBox_8->setValue(2);
    ui->spinBox_8->setDisabled(false);
    ui->radioButton->setDisabled(false);
    ui->radioButton_2->setDisabled(false);
    ui->radioButton->setChecked(true);
    ui->radioButton_3->setChecked(true);
    ui->horizontalSlider_2->setDisabled(true);
    ui->horizontalSlider_2->setValue(1);
    ui->spinBox_3->setValue(0);
    ui->spinBox_4->setValue(0);
    ui->spinBox_5->setValue(1);
    ui->spinBox_6->setValue(1);
    init();
}

void MainWindow::write(QString s){
    ui->textout->append(s);
}

void MainWindow::on_pushButton_3_clicked()
{
    system("gedit log.txt");
}


// Inital value assignments


void MainWindow::on_spinBox_7_valueChanged(int arg1)
{
    qlength=arg1;
}

void MainWindow::on_radioButton_3_clicked()
{
    burst='r';
}

void MainWindow::on_radioButton_4_clicked()
{
    burst='m';
    burst_size=ui->horizontalSlider_2->value();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    burst_size=ui->horizontalSlider_2->value();
}

void MainWindow::on_radioButton_clicked()
{
    state='r';
}

void MainWindow::on_radioButton_2_clicked()
{
    state='m';
}

void MainWindow::on_spinBox_8_valueChanged(int arg1)
{
    num=arg1;
}

void MainWindow::on_spinBox_6_valueChanged(int arg1)
{
    sn=arg1;
}

void MainWindow::on_spinBox_5_valueChanged(int arg1)
{
    pn=arg1;
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    nn=arg1;
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    en=arg1;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    loss=value;
}

void MainWindow::on_pushButton_clicked()
{
    ui->spinBox->setDisabled(true);
    ui->spinBox_3->setDisabled(true);
    ui->spinBox_4->setDisabled(true);
    ui->spinBox_5->setDisabled(true);
    ui->spinBox_6->setDisabled(true);
    ui->spinBox_7->setDisabled(true);
    ui->spinBox_8->setDisabled(true);
    ui->radioButton->setDisabled(true);
    ui->radioButton_2->setDisabled(true);

    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.

    worker->requestWork();
}

void MainWindow::on_pushButton_2_clicked()
{
    worker->abort();
    thread->wait();
    reset();
}

void MainWindow::on_pushButton_4_clicked()
{
    m1.lock();
    plus_node++;
    m1.unlock();
}

void MainWindow::on_pushButton_5_clicked()
{
    m1.lock();
    minus_node++;
    m1.unlock();
}

void MainWindow::on_pushButton_6_clicked()
{
    m2.lock();
    plus_job++;
    m2.unlock();
}

void MainWindow::on_pushButton_7_clicked()
{
    m2.lock();
    minus_job++;
    m2.unlock();
}
