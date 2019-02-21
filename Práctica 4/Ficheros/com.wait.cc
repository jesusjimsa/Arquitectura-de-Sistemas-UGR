//---------------------------------------------------------
// com.wait.cc
//---------------------------------------------------------

#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

//---------------------------------------------------------

int main()
{
	int msg = 0;
	pid_t hijo = fork();

	switch(hijo)
	{
		case -1: 
			std::cout << "fallo en fork()!";
			break;
		case 0:
			msg = 123;
			std::cout << "hijo  --> " 
			          << msg << std::endl;
			exit(msg);
			break;
		default: 
			wait(&msg);
			std::cout << "padre --> " 
			          << WEXITSTATUS(msg) << std::endl;
			break;
	}
}

//---------------------------------------------------------

