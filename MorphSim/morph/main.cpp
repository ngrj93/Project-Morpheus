#include <QSharedMemory>
#include <iostream>
#include <QDebug>
#include <ctime>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QSharedMemory shm;
    shm.setKey("myMemory");
    if(!shm.attach()){
        QString s=shm.errorString();
        qDebug() << s;
    }
    qDebug() << "hello";
    srand(time(NULL));
    int t=rand()%3+1;
    usleep(t*1000000);

    int nodeid=atoi(argv[1]);

    shm.lock();
    int *p=(int *)shm.data();
    p[nodeid]--;
    shm.unlock();
    shm.detach();
}
