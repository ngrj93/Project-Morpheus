#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>
#include <QSharedMemory>

#include "ui_mainwindow.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    void requestWork();
    void setUi(Ui::MainWindow *);
    void abort();
    void write(QString);

private:
    bool _working;
    bool _abort;
    QMutex mutex;
    QSharedMemory shm;
    Ui::MainWindow *ui;

signals:
    void workRequested();
    void finished();

public slots:
    void doWork();
private slots:
};

#endif // WORKER_H
