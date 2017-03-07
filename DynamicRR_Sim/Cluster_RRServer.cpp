#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<cstdlib>
#include<ctime>
#include<unistd.h>
#include<vector>
#include<string.h>
#define SERVPORT 32000
#define LQUEUE 5
using namespace std;

bool NonZero(vector<int> p){
	for(int i=0;i<p.size();i++)
		if(p[i])
			return true;
	return false;
}

int GetMin(vector<int> p){
	int min=51;
	for(int i=0;i<p.size();i++)
		if(p[i]!=0)
			min=min<p[i]?min:p[i];
	return min;
}

int main(){
	srand(time(NULL));
	int sock,clisock;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr,cliaddr;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
		cout<<"Exception 1"<<endl;
		return -1;
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERVPORT);
	servaddr.sin_addr.s_addr=htons(INADDR_ANY);
	if(bind(sock,(struct sockaddr *) &servaddr,sizeof(servaddr))<0){
		cout<<"Exception 2"<<endl;
		return -1;
	}
	listen(sock,LQUEUE);
	cout<<"Cluster node 1 started....."<<endl;
	if((clisock=accept(sock,(struct sockaddr *) &cliaddr,(socklen_t *)&len))<0){
		cout<<"Exception 3"<<endl;
		return -1;
	}
	
	int n,perc,q,bound;
	cout<<"Enter the number of jobs that you would like to process: ";
	cin>>n;
	cout<<endl<<"Assigning random cluster node capability for load distribution..."<<endl;
	cout<<"Node 1 load capability is "<<(perc=rand()%100)<<endl;
	cout<<"Node 2 load capability is "<<100-perc<<endl;
	cout<<endl<<"Creating jobs with random execution burst times (btw 1 and 50 ms)... "<<endl;
	vector<int> process1,process2;
	bound=(int)(n*((double)perc/100));
	string s="";
	for(int i=1;i<=bound;i++){
		process1.push_back(rand()%50+1);
		cout<<"Job "<<i<<" burst size = "<<process1[i-1]<<endl;
	}
	for(int i=0;i<n-bound;i++){
		process2.push_back(rand()%50+1);
		cout<<"Job "<<bound+1+i<<" burst size = "<<process2[i]<<endl;
		s=s+to_string(process2[i])+" ";
	} 
	cout<<"Enter the time quantum: "<<endl;
	cin>>q;
	s=to_string(bound+1)+" "+to_string(q)+" "+s;
	write(clisock,s.c_str(),s.size());
	cout<<endl<<"----------------------------"<<endl;
	
	float waiting_time=0,turnaround_time=0;
	
	for(int i=0;i<process1.size();i++)
		turnaround_time+=process1[i];
	
	cout<<"Node 1 execution statistics"<<endl<<endl;
	while(NonZero(process1)){
		int min=GetMin(process1);
		min=min>q?q:min;
		cout<<"The time quantum for the current run is "<<min<<endl;
		for(int i=0;i<process1.size();i++){
			if(process1[i]){
				if(process1[i]>min){
					process1[i]-=min;
					cout<<"Process "<<i+1<<" execution time remaining is "<<process1[i]<<" ms"<<endl;
					waiting_time+=min;
				}
				else{
					waiting_time+=process1[i];
					process1[i]=0;
					cout<<"Process "<<i+1<<" has finished executing!"<<endl;
				}
			}
		}
		waiting_time-=min;
		cout<<endl;
	}
	
	turnaround_time+=waiting_time;
	
	cout<<"The average waiting time for the processes in node 2 is "<<waiting_time/process1.size()<<"ms"<<endl;
	cout<<"The average turnaround time for the processes in node 2 is "<<turnaround_time/process1.size()<<"ms"<<endl;
	
	return 0;
}
	
	
