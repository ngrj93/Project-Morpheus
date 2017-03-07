#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<vector>
#include<arpa/inet.h>
#include<cstdio>
#define SERVPORT 32000
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
	int sock;
	struct sockaddr_in servaddr;
	char buffer_in[1024];
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
		cout<<"Exception 1"<<endl;
		return -1;
	}
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERVPORT);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr))<0){
		cout<<"Exception 2"<<endl;
		return -1;
	}
	cout<<"Cluster node 2 started....."<<endl;
	int nr=read(sock,buffer_in,1024);
	int temp=0,count=-2,bound,q;
	vector<int> process;
	for(int i=0;i<nr;i++){
		if(isdigit(buffer_in[i]))
			temp=temp*10+(buffer_in[i]-48);
		else if(count==-2){
			bound=temp;
			count++;
			temp=0;
		}
		else if(count==-1){
			q=temp;
			count++;
			temp=0;
		}
		else{
			process.push_back(temp);
			count++;
			temp=0;
		}
	}
	
	float waiting_time=0,turnaround_time=0;
	
	for(int i=0;i<process.size();i++){
		cout<<process[i]<<" ";
		turnaround_time+=process[i];
	}
		
	cout<<endl<<"----------------------------"<<endl;
	cout<<"Node 2 execution statistics"<<endl<<endl;
	while(NonZero(process)){
		int min=GetMin(process);
		min=min>q?q:min;
		cout<<"The time quantum for the current run is "<<min<<endl;
		for(int i=0;i<process.size();i++){
			if(process[i]){
				if(process[i]>min){
					process[i]-=min;
					cout<<"Process "<<bound+i<<" execution time remaining is "<<process[i]<<" ms"<<endl;
					waiting_time+=min;	
				}
				else{
					waiting_time+=process[i];
					process[i]=0;
					cout<<"Process "<<bound+i<<" has finished executing!"<<endl;

				}
			}
		}
		waiting_time-=min;
		cout<<endl;
	}
	
	turnaround_time+=waiting_time;
	
	cout<<"The average waiting time for the processes in node 2 is "<<waiting_time/process.size()<<"ms"<<endl;
	cout<<"The average turnaround time for the processes in node 2 is "<<turnaround_time/process.size()<<"ms"<<endl;
	return 0;
}
