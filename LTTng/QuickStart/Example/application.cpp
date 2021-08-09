#define TRACEPOINT_DEFINE
#include "TPprovider.h"


int main(int argc, char* argv[])
{

	if(argc > 2)
	{
		int a1 =std::atoi(argv[1]);
		size_t a2 = std::atoi(argv[2]);
		tracepoint(example_provider, get_setting, a1 , a2 );
	}

	return 0;
}
