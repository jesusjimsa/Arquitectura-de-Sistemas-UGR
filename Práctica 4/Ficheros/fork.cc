//---------------------------------------------------------
// fork.cc
//---------------------------------------------------------

#include <unistd.h>
#include <iostream>

//---------------------------------------------------------

int main()
{
	switch(fork())
	{
		case -1: std::cout << "fallo en fork()!"; break;
		case  0: std::cout << "hijo";             break;
		default: std::cout << "padre";            break;
	}
	std::cout << "\t [" << getpid() << "]" << std::endl;
}

//---------------------------------------------------------

