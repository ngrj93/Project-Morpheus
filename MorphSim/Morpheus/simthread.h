#ifndef SIMTHREAD_H
#define SIMTHREAD_H
#include<QThread>

class SimThread:public QThread{
    Q_OBJECT
public:
    SimThread();
    void stop();
protected:
    void run();
private:
    volatile bool stopped;
};

#endif // SIMTHREAD_H
