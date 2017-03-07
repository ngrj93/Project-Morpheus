#ifndef GLOBSHARE_H
#define GLOBSHARE_H
#include<QMutex>

extern volatile int num;
extern volatile int burst_size;
extern volatile int qlength;
extern volatile char burst;
extern volatile int jobs;
extern volatile char state;
extern volatile int sn;
extern volatile int pn;
extern volatile int nn;
extern volatile int en;
extern volatile int loss;
extern volatile int minus_node;
extern volatile int plus_node;
extern volatile int plus_job;
extern volatile int minus_job;
extern QMutex m1,m2;

#endif // GLOBSHARE_H
