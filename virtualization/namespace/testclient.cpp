#include <iostream>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

	int writefd  = std::atoi(argv[1]);
	int readfd = std::atoi(argv[2]);


	std::cout<<"writefd : "<<writefd<<std::endl;
	std::cout<<"readfd : "<<readfd<<std::endl;



	char buffer[255]="continous write";



	if(unshare(CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWUSER) == -1)
	{
		std::cerr<<"unshare failed : "<<errno<<std::endl;
		return 1;
	}

	while(true)
	{
		write(writefd, buffer, strlen(buffer));
		sleep(10);
	}


	return 0;
}
