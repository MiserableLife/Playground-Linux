#include <iostream>
#include <string>
#include <unistd.h>


int pipefd[4];


int main()
{
	if( pipe(pipefd) == -1  ) 
	{
		perror("pipe");
		exit(1);
	}
	if( pipe(pipefd+2) == -1  ) 
	{
		perror("pipe");
		exit(1);
	}

	if(fork() == 0 )
	{
		char* const args[] = {(char*)"client",(char*)std::to_string(pipefd[1]).c_str(), (char*)std::to_string(pipefd[2]).c_str(), nullptr};

		if(execv("client", args) == -1)
		{
			std::cerr<<"error to spawn ("<<errno<<")"<<std::endl;
		}
	}


	char buffer[255];
	int read_num{};
	while(true)
	{
		read_num = read(pipefd[0], buffer, 255);
		for(int i=0; i<read_num; i++)
			printf("%c",buffer[i]);
		printf("\n");

	}




	




	return 0;
}
