//-----------------------------------------------------------------------------
// fork_c.cc
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>

//-----------------------------------------------------------------------------

int main()
{
	switch(fork())
	{
		case -1: printf("fallo en fork()!"); break;
		case  0: printf("hijo"); break;
		default: printf("padre"); break;
	}
	printf("\t [%d]\n", getpid());
	return 0;
}

//-----------------------------------------------------------------------------

