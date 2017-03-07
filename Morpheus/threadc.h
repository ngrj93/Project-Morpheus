#ifndef THREAD_H
#define THREAD_H

#include<QThread>

class Thread: public QThread{
    Q_OBJECT
public:
    Thread();
    void setStopped(bool);
    void stop();
protected:
    void run();
private slots:
    void deleteLater();
signals:
    void finished();
private:
    volatile bool stopped;
};

#endif // THREAD_H
