#include <dlfcn.h>
#include <iostream>

typedef void* (*mallocfunc)(size_t);
void* malloc(size_t size)
{
	static void* (*my_malloc)(size_t) = nullptr;
	my_malloc =  (mallocfunc)dlsym(RTLD_NEXT, "malloc") ;
	std::cout<<"hooked malloc called!"<<std::endl;
	return my_malloc(size);
}
