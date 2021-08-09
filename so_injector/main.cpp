#include <iostream>
#include <stdlib.h>
#include <malloc.h>

int main()
{

	int *p = (int*)malloc(10);
	free(p);
	return 0;
}

