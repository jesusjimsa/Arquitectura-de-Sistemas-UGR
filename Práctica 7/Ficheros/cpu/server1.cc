// unlimited number of processes

#include <sys/wait.h>
#include <unistd.h>
#include "work.h"

int main()
{
	for (int i = 0; i < N; ++i)
		switch(fork())
		{
			case -1: return 1;
			case  0: work(i, i + 1); return 0;
			default: wait(NULL);
		}
}
