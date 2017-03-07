#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include<ctime>
#include<unistd.h>
#include<cstdlib>
using namespace boost::interprocess;

typedef allocator<int, managed_shared_memory::segment_manager>  ShmemAllocator;

typedef vector<int, ShmemAllocator> MyVector;


int main(int argc,char* argv[]){
	
	managed_shared_memory segment(open_only, "MySharedMemory");

	MyVector *myvector = segment.find<MyVector>("MyVector").first;

	srand(time(NULL));
	int t=rand()%3+1;
	usleep(t*1000000);
	
	int nodeid=atoi(argv[1]);
	int jobid=atoi(argv[2]);
	std::cout<<"--> Node ID "<<nodeid+1<<" finished execution of job ID "<<jobid<<" <--"<<std::endl;
	(*myvector)[nodeid]--;
	return 0;
}
