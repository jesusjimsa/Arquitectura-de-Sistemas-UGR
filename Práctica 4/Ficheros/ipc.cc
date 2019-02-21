//---------------------------------------------------------
// ipc.cc
//---------------------------------------------------------

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

//---------------------------------------------------------

int main(int argc, char* argv[])
{
	switch(fork())
	{
	case -1: 
		std::cerr << argv[0] << ": error en fork()" << std::endl;
		break;
	case 0: 
		std::cout << "hijo:	" << getpid() << std::endl;
		exit(123);
		break;
	default:
		int estado;
		std::cout << "padre: " << getpid() << std::endl; 
		wait(&estado);
		std::cout << "hijo --> padre: " << WEXITSTATUS(estado) << std::endl;
		break;
	}
}

//---------------------------------------------------------

