// optimal number of processes

#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <unistd.h>
#include "work.h"

int main()
{
	int P = get_nprocs();
	
	for (int i = 0; i < P; ++i)
		switch(fork())
		{
			case -1: return 1;
			case  0: work(i * (N / P), (i + 1) * (N / P)); return 0;
			default: wait(NULL);
		}
}
