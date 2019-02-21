#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>

//---------------------------------------------------------

int ping = 0, pong = 0;

//---------------------------------------------------------

void show_ping(int)
{
	std::cout << "ping = " << ping << std::endl;
	exit(EXIT_SUCCESS);
}

//---------------------------------------------------------

void show_pong(int)
{
	std::cout << "pong = " << pong << std::endl;
	exit(EXIT_SUCCESS);
}

//---------------------------------------------------------

int main()
{
	const char PING = '1', PONG = '0';

	auto address = mmap(nullptr, 1, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);

	volatile char& table = *static_cast<volatile char*>(address);
	table = PONG;

	switch(fork())
	{
		case -1: // fallo
			std::cout << "fallo en fork()!" << std::endl; 
			exit(EXIT_FAILURE); 
			break;
		case  0: // hijo
			signal(SIGALRM, show_pong);
			alarm(1);
			while (true)
			{
				while (table == PONG);
				table = PONG;
				++pong;
			}
			break;
		default: // padre
			signal(SIGALRM, show_ping);
			alarm(1);
			while (true)
			{
				while (table == PING);
				table = PING;
				++ping;
			}
			wait(nullptr);
			break;
	}
}
