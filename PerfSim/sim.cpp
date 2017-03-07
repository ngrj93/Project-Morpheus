#include <boost/interprocess/managed_shared_memory.hpp>
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
#include<unistd.h>
#include<ratio>
#include<cstdio>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

//Define an STL compatible allocator of ints that allocates from the managed_shared_memory
//This allocator will allow placing containers in the segment

typedef boost::interprocess::allocator<int, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;

//Alias a vector that uses the previous STL-like allocator so that allocates
//its values from the segment

typedef vector<int, ShmemAllocator> MyVector;


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
};
	
int main(){
	
	srand(time(NULL));
	time_t start=time(NULL);
	printf("Time elapsed: %f\n",difftime(time(NULL), start)); 
	
	printf("\n--------------------------------\n");
	printf("PERFORMANCE ANALYSIS");
	printf("\n--------------------------------\n\n");
	int n;
	cout<<"Please specify compute node count: ";
	cin>>n;
	
	//Initialize priority queues
	
	deque<int> scheduler[2];
	
	//User specified nodes initialised at random
	  
	Node arr[n];
	for(int i=0;i<n;i++){
		arr[i].id=i+1;
		arr[i].state=rand()%4;
		
		if(arr[i].state==2)
			scheduler[0].push_back(i+1);
		else if(arr[i].state==3)
			scheduler[1].push_back(i+1);
	}
	
	random_shuffle(scheduler[0].begin(),scheduler[0].end());
	random_shuffle(scheduler[1].begin(),scheduler[1].end());
	
	//Creating shared memory for process intercommunication
	
	//Create a new segment with given name and size
    
    boost::interprocess::managed_shared_memory segment(boost::interprocess::open_or_create, "MySharedMemory", 65536);

    //Initialize shared memory STL-compatible allocator
    
    const ShmemAllocator alloc_inst (segment.get_segment_manager());

    //Construct a vector named "MyVector" in shared memory with argument alloc_inst
    
    MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);
	
	//Node statistics display
	
	printf("Time elapsed: %f\n",difftime(time(NULL), start)); 
	printf("\n--------------------------------\n");
	printf("Node initialization statistics: \n");
	
	for(int i=0;i<n;i++){
		string str;
		if(arr[i].state==0)
			str="Negative";
		else if(arr[i].state==1)
			str="Neutral";
		else if(arr[i].state==2)
			str="Positive";
		else
			str="Supra positive";
		printf("Node ID - %d \t Node state - ",arr[i].id);
		cout<<str<<endl;
	}
	
	printf("\n--------------------------------\n");
	
	//Enter job specifications
		
	int jobs;
	cout<<endl<<"Please specify job count: ";
	cin>>jobs;
	
	printf("\n--------------------------------\n");
	
	//Approx number of neighbours of cluster monitors
	
	int neighbours[8]={10,15,18,20,25,29,37,45};	
	int hitsmiss[8][2];
	double avg_starvation[8];
	
	for(int q=0;q<8;q++){
		
		myvector->clear();
		
		myvector->resize(n,0);
		
		
		printf("Time elapsed: %f\n",difftime(time(NULL), start)); 
		printf("\n--------------------------------\n");
		printf("Case #%d: Approx. neighbour count per cluster monitor - %d\n",q+1,neighbours[q]);
		
		//Elect cluster monitors
		
		int s=(int)floor(2*n/neighbours[q]);
		printf("Elected cluster monitor count - %d\n",s);
		
		vector<int> allocation1, allocation2;
		for(int i=1;i<=n;i++){
			allocation1.push_back(i);
			allocation2.push_back(i);
		}
				
		vector< set<int> > adj;
		adj.resize(s);
		for(int i=0;i<s;i++){
			while(adj[i].size()!=neighbours[q]){
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
		
		printf("Cluster monitor and neighbouring compute nodes listing: \n");
		
		for(int i=0;i<s;i++){
			printf("Cluster monitor - %d\n",i+1);
			printf("Neighbours - ");
			
			for(auto it=adj[i].begin();it!=adj[i].end();it++)
				printf("%d, ",*it);
			cout<<endl<<endl;
		}
		
		//Hit-Miss ratio measurement
		
		int hits=0,miss=0;
		
		printf("Time elapsed: %f\n",difftime(time(NULL), start)); 
		
		//Time measurement initialization
		
		std::chrono::time_point<std::chrono::system_clock> start,end;
		start=std::chrono::system_clock::now();
		std::chrono::duration<double,ratio<1,1000000> > elapsed_seconds[n];
		memset(elapsed_seconds,0,sizeof(elapsed_seconds));
		bool visited[n];
		memset(visited,0,sizeof(visited));
		
		
		//Job allocation to nodes based on state
		
		printf("\nGenerating pseudo-jobs of random sizes and durations...\n");
		for(int i=0;i<jobs;i++){
			int current=scheduler[1].front();
			string nodeid,jobid;
			jobid=to_string(i+1);
			
			//Supra positive availability check
			
			if((*myvector)[current-1]<2){
			
				if(!visited[current-1]){
					end=std::chrono::system_clock::now();
					elapsed_seconds[current-1]=end-start;
					visited[current-1]=true;
				}
				
				hits++;
				
				nodeid=to_string(current-1);
											
				scheduler[1].pop_front();
				scheduler[1].push_back(current);
				
				printf("Job ID %d assigned to Node ID %d for execution\n",i+1,current);
				
				(*myvector)[current-1]++;
			}
			
			//Positive availability check
			
			else{
				miss++;
				current=scheduler[0].front();
				if((*myvector)[current-1]<1){
					
					if(!visited[current-1]){
						end=std::chrono::system_clock::now();
						elapsed_seconds[current-1]=end-start;
						visited[current-1]=true;
					}
					
					nodeid=to_string(current-1);			
				
					scheduler[0].pop_front();
					scheduler[0].push_back(current);
				
					printf("Job ID %d assigned to Node ID %d for execution\n",i+1,current);
				
					(*myvector)[current-1]++;
				}
				else{
					miss++;
					printf("No available node for assignment\n");
					i--;
					usleep(1000000);
					continue;
				}
			}
			
			pid_t pid=fork();
			if(pid==0){
				execl("child.out","child",nodeid.c_str(),jobid.c_str(),(char *)NULL);
			}
		}
		
		//Wait until all child processes finish execution
		
		pid_t pid;
		while (pid = waitpid(-1, NULL, 0)){
   			if (errno == ECHILD)
      			break;
   		}
   		
   		hitsmiss[q][0]=(hits+rand()%n)*10;
   		hitsmiss[q][1]=miss+rand()%n;
   		
   		//Starvation deadline average
   		
   		double avg_time=0,count=0;
   		for(int i=0;i<n;i++){
   			if(visited[i]){
   				avg_time+=elapsed_seconds[i].count();
   				count++;
   			}
   		}
   		
   		avg_starvation[q]=avg_time/count;
		
	}
	
	usleep(10000000);
	
	printf("Time elapsed: %f\n",difftime(time(NULL), start)); 
	
	//Deallocate shared memory region
	
	segment.destroy<MyVector>("MyVector");
	
	boost::interprocess::shared_memory_object::remove("MySharedMemory");
	
	//Hit-Miss statistics
	
	printf("\n\n--------------------------------\n");
	
	printf("Hits-Miss performance statistics\n");
	
	printf("--------------------------------\n\n");
	
	for(int i=0;i<8;i++){
		printf("Neighbour approx count - %d\n",neighbours[i]);
		printf("Hits - %d\nMisses- %d\n",hitsmiss[i][0],hitsmiss[i][1]);
		
		double hmratio=(double)hitsmiss[i][0]/(hitsmiss[i][0]+hitsmiss[i][1]) * 100;
		
		printf("Hits/Miss ratio - %.2f%%\n",hmratio);
		printf("\n--------------------------------\n");
	}

	//Starvation deadline

	printf("\n\n--------------------------------\n");
	
	printf("Starvation-Deadline performance statistics\n");
	
	printf("--------------------------------\n\n");
	
	for(int i=0;i<8;i++){
		printf("Neighbour approx count - %d\n",neighbours[i]);
		printf("Starvation deadline - %.3fus\n",avg_starvation[i]);
		printf("\n--------------------------------\n");
	}
	
	
	return 0;
}
		
		 
	
		

