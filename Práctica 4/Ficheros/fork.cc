//---------------------------------------------------------
// fork.cc
//---------------------------------------------------------

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

//---------------------------------------------------------

int main()
{
	switch(fork())
	{
		case -1: std::cout << "fallo en fork()!";     break;
		case  0: std::cout << "hijo";                 break;
		default: wait(nullptr); std::cout << "padre"; break;
	}
	std::cout << "\t [" << getpid() << "]" << std::endl;
}

//---------------------------------------------------------

