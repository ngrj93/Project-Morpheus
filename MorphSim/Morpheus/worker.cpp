#include"worker.h"
#include<boost/interprocess/managed_shared_memory.hpp>
#include<boost/interprocess/containers/vector.hpp>
#include<boost/interprocess/allocators/allocator.hpp>
#include<deque>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<set>
#include<vector>
#include<cmath>
#include<map>
#include<sys/mman.h>
#include<cstdlib>
#include<cstring>
#include<string>
#include<chrono>
#include<queue>
#include<unistd.h>
#include<ratio>
#include<cstdio>
#include<sys/types.h>
#include<sys/wait.h>
#include<threadc.h>
#include<fstream>
#include<globshare.h>
#include<QTimer>
#include<QDebug>
#include<iomanip>
#include<QProcess>
using namespace std;


class Node{
public:
    int id;
    int state;
    int role;
    Node(){
        id=0;
        state=1;
        role=0;
    }
    Node(int id){
        this->id=id;
        state=1;role=0;
    }
};

void Worker::doWork(){

    srand(time(NULL));
    clock_t begin = clock();
    ofstream fout("log.txt");
    fout << "This log file contains details of the latest simulation run!\n" << endl;
    fout << "Simulation starting time: "<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<endl;
    fout << "\n--------------------------------\n";

    fout<<endl<< "Loading and initializing resources: <standby>"<<endl<<endl;

    //Gnuplot file

    ofstream outf("/home/nagaraj/hits.dat");

    deque<int> scheduler[2];

    if(state=='m')
        num=sn+pn+nn+en;

    //User specified nodes initialised at random

    vector<Node> arr;
    arr.resize(num);

    if(!shm.attach())
        shm.create(5000);
    shm.attach();
    shm.lock();
    int *p=(int *)shm.data();
    for(int i=0;i<600;i++)
        p[i]=0;
    shm.unlock();

    if(state=='r'){
        for(int i=0;i<num;i++){
            arr[i].id=i+1;
            arr[i].state=rand()%4;
            fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";
            fout << "Node "<<i+1<<" connected and initialised"<<endl;
            if(arr[i].state==1)
                en++;
            if(arr[i].state==2){
                scheduler[0].push_back(i+1);
                pn++;
            }
            else if(arr[i].state==3){
                scheduler[1].push_back(i+1);
                sn++;
            }
        }
    }
    else{
        int k=0;
        for(int i=1;i<=sn;i++){
            arr[k].id=k+1;
            arr[k].state=3;
            scheduler[1].push_back(k+1);
            fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";
            fout << "Supra-positive node "<<k+1<<" connected and initialised"<<endl;
            k++;
        }
        for(int i=1;i<=pn;i++){
            arr[k].id=k+1;
            arr[k].state=2;
            scheduler[0].push_back(k+1);
            fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";
            fout << "Positive node "<<k+1<<" connected and initialised"<<endl;
            k++;
        }
        for(int i=1;i<=nn;i++){
            arr[k].id=k+1;
            arr[k].state=0;
            fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";
            fout << "Negative node "<<k+1<<" connected and initialised"<<endl;
            k++;
        }
        for(int i=1;i<=en;i++){
            arr[k].id=k+1;
            arr[k].state=1;
            fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";
            fout << "Neutral node "<<k+1<<" connected and initialised"<<endl;
            k++;
        }
    }

    random_shuffle(scheduler[0].begin(),scheduler[0].end());
    random_shuffle(scheduler[1].begin(),scheduler[1].end());

    fout<<endl<< "Time elapsed: "<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<endl;

    //Node statistics display

    fout << "\n--------------------------------\n\n";
    fout << "Node initialization statistics: \n\n";

    for(int i=0;i<num;i++){
        string str;
        if(arr[i].state==0)
            str="Negative";
        else if(arr[i].state==1)
            str="Neutral";
        else if(arr[i].state==2)
            str="Positive";
        else
            str="Supra positive";
        fout << "Node ID - "<<arr[i].id<<" \t Node state - ";
        fout << str<<endl;
    }

    fout << endl<< "Time elapsed: "<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<endl;

    fout << "\n--------------------------------\n\n";

    if(qlength>num)
        qlength=num;
    fout << "Approx. neighbour count per cluster monitor - "<<qlength<<"\n";

    int s=(int)floor(2*num/qlength);
    fout << "Elected cluster monitor count - "<<s<<"\n";

    //Elect cluster monitors

    vector<int> allocation1, allocation2;
    for(int i=1;i<=num;i++){
       allocation1.push_back(i);
       allocation2.push_back(i);
    }

    vector< set<int> > adj;
    adj.resize(s);
    for(int i=0;i<s;i++){
       while(adj[i].size()!=qlength){
           int lisize1=allocation1.size(),lisize2=allocation2.size();
           int temp=(lisize1>0)?rand()%lisize1:rand()%lisize2;
           if(lisize1>0){
               if(!adj[i].count(allocation1[temp])){
                   adj[i].insert(allocation1[temp]);
                   allocation1.erase(allocation1.begin()+temp);
               }
           }
           else{
               if(!adj[i].count(allocation2[temp])){
                   adj[i].insert(allocation2[temp]);
                   allocation2.erase(allocation2.begin()+temp);
               }
           }
       }
    }

    //Listing of cluster monitors and their appointed neighbours

    fout<<"\nCluster monitor and neighbouring compute nodes listing: \n";

    for(int i=0;i<s;i++){
       fout << "Cluster monitor - "<<i+1<<"\n";
       fout << "Neighbours - ";

       for(auto it=adj[i].begin();it!=adj[i].end();it++)
           fout<<*it<<", ";
       fout << endl<<endl;
    }

    fout << "Time elapsed: "<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<endl;

    fout << "\n--------------------------------\n\n";

    //Starvation deadline

    double starvation=0;

    //Hit-Miss ratio measurement

    vector<bool> visited;
    visited.resize(num,0);
    int total=num;

    int hits=0,miss=0;
    int j_id=1;
    QString program = "gnuplot /home/nagaraj/loop.plt";
    QProcess *myProcess = new QProcess(this);
    myProcess->startDetached(program);

    while (true){

        mutex.lock();
        bool abort = _abort;
        mutex.unlock();
        if(abort)
            break;

        m1.lock();
        while(plus_node){
            int tempstate=rand()%4;
            if(tempstate==2)
                scheduler[0].push_front(num+1);
            else if(tempstate==3)
                scheduler[1].push_front(num+1);
            Node in(++num);
            arr.push_back(in);
            visited.push_back(0);
            total++;
            int temp=rand()%s;
            fout<<"New Node "<<num<<" connected and initialized"<<endl;
            fout<<"Node "<<num<<" has been assigned under the purvey of cluster monitor "<<temp<<endl;
            plus_node--;
        }
        m1.unlock();

        m2.lock();
        while(plus_job){
            jobs++;
            fout<<"New job added for processing!"<<endl;
            plus_job--;
        }
        m2.unlock();

        m1.lock();
        while(minus_node){
            if(num>0){
                arr.pop_back();
                fout<<"Node "<<num<<" disconnected"<<endl;
                bool flag=0;
                for(int i=0;i<scheduler[0].size();i++){
                    if(scheduler[0][i]==num){
                        scheduler[0].erase(scheduler[0].begin()+i);
                        flag=1;
                        break;
                    }
                }
                if(!flag){
                    for(int i=0;i<scheduler[1].size();i++){
                        if(scheduler[1][i]==num){
                            scheduler[1].erase(scheduler[1].begin()+i);
                            break;
                        }
                    }
                }
                num--;
                minus_node--;
            }
        }
        m1.unlock();

        m2.lock();
        while(minus_job){
            if(jobs>0){
                jobs--;
                fout<<"1 job removed"<<endl;
            }
            else
                fout<<"No job to remove"<<endl;
            minus_job--;
        }
        m2.unlock();

        while(jobs>0){

            mutex.lock();
            bool abort = _abort;
            mutex.unlock();
            if(abort)
                break;

            int current=scheduler[1].front();
            string nodeid,jobid;
            jobid=to_string(j_id);

            int meter=5-loss+3;
            int random_val=rand()%meter;

            if(!random_val){
                miss++;
                outf<<setiosflags(ios::fixed)<<setprecision(3)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<" "<<-1<<endl;
                switch(rand()%3){
                case 0: fout<<endl<<"Destination compute node not reachable!"<<endl;
                        break;
                case 1: fout<<endl<<"Node failure! Rebooting and recheduling..."<<endl;
                        break;
                case 2: fout<<endl<<"Corrupted data! Job restarting..."<<endl;
                        j_id--;
                        jobs++;
                        break;
                }
                continue;
            }


            //Supra positive availability check

            if(p[current-1]<2){

                if(!visited[current-1]){
                    starvation+=(float)(clock()-begin)/CLOCKS_PER_SEC;
                    visited[current-1]=true;
                }

                hits+=10;
                outf<<setiosflags(ios::fixed)<<setprecision(3)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<" "<<10<<endl;
                fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";

                nodeid=to_string(current-1);

                scheduler[1].pop_front();
                scheduler[1].push_back(current);

                fout<<"Job ID "<<j_id<<" assigned to Node ID "<<current<<" for execution\n\n";

                p[current-1]++;
            }

            //Positive availability check

            else{
                miss++;
                current=scheduler[0].front();
                if(p[current-1]<1){

                    if(!visited[current-1]){
                        starvation+=(float)(clock()-begin)/CLOCKS_PER_SEC;
                        visited[current-1]=true;
                    }

                    fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";

                    nodeid=to_string(current-1);

                    scheduler[0].pop_front();
                    scheduler[0].push_back(current);

                    fout<<"Job ID "<<j_id<<" assigned to Node ID "<<current<<" for execution\n\n";

                    p[current-1]++;
                    hits+=7;
                    outf<<setiosflags(ios::fixed)<<setprecision(3)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<" "<<-1<<endl;
                }
                else{
                    miss++;
                    outf<<setiosflags(ios::fixed)<<setprecision(3)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<" "<<-1<<endl;
                    fout << "["<<setiosflags(ios::fixed)<<setprecision(6)<<(float)(clock()-begin)/CLOCKS_PER_SEC<<"] ";
                    fout<<"No available node for assignment\n\n";
                    sleep(1);
                    continue;
                }
            }
            jobs--;
            j_id++;

            pid_t pid=fork();
            if(pid==0){
                execl("/home/nagaraj/mor","mor",nodeid.c_str(),(char *)NULL);
            }

        }

        pid_t pid;
        while (pid = waitpid(-1, NULL, 0)){
            if (errno == ECHILD)
                break;
        }

    }

    write("----------------------------------------------------------------");
    write("<h3><font color=\"blue\">Begin</font></h3>");
    write("----------------------------------------------------------------");

    double hitratio=(double)hits/(hits+miss)*100;
    stringstream stream;
    stream << fixed << setprecision(2) << hitratio;
    string tempstr = stream.str();
    tempstr="<h3>Hit/Miss Ratio - <font color=\"green\">"+tempstr+"%</font></h3>";
    write(QString::fromStdString(tempstr));
    write("----------------------------------------------------------------");
    stream.str("");
    stream << fixed <<setprecision(2)<< starvation/total*1000000;
    tempstr=stream.str();
    tempstr="<h3>Max Starvation Deadline - <font color=\"green\">"+tempstr+"us</font></h3>";
    write(QString::fromStdString(tempstr));
    write("----------------------------------------------------------------");
    stream.str("");
    double response_time=(double)burst_size/100+(double)(rand()%10)/1000;
    stream << fixed <<setprecision(3)<< response_time;
    tempstr=stream.str();
    tempstr="<h3>Average Response Time - <font color=\"green\">"+tempstr+"ms</font></h3>";
    write(QString::fromStdString(tempstr));
    write("----------------------------------------------------------------");
    stream.str("");
    double resutil=(double)(sn+pn+en)/num*100;
    stream << fixed <<setprecision(2)<< resutil;
    tempstr=stream.str();
    tempstr="<h3>Average Resource Utilisation - <font color=\"green\">"+tempstr+"%</font></h3>";
    write(QString::fromStdString(tempstr));
    write("----------------------------------------------------------------");
    write("<h3><font color=\"red\">End!</font></h3>");
    write("----------------------------------------------------------------");

    myProcess->kill();
    shm.detach();
    mutex.lock();
    _working = false;
    mutex.unlock();

    emit finished();

}


//---------------------------------------------------------------------------------------------------------------------


Worker::Worker(QObject *parent) :
    QObject(parent),shm("myMemory")
{
    _working = false;
    _abort = false;
    shm.create(5000);
}

void Worker::setUi(Ui::MainWindow *ui){
    this->ui=ui;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();
    qDebug()<<"Request worker starting in Thread ";
    emit workRequested();
}

void Worker::abort()
{
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();

    }
}

void Worker::write(QString s){
    ui->simres->append(s);
}
