#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

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
	const int RD = 0, WR = 1;

	int mesa[2][2];

	for (int i = 0; i < 2; ++i)
		if (pipe(mesa[i]))
			throw std::runtime_error("pipe failed with error code: " + 
			                         std::to_string(errno));

	switch(fork())
	{
		case -1: 
			// fallo
			std::cout << "fallo en fork()!" << std::endl; 
			exit(EXIT_FAILURE); 
			break;
		case 0:
			// hijo
			signal(SIGALRM, show_pong);
			alarm(1);
			while (true)
			{
				char c;
				write(mesa[1][WR], &PONG, 1);
				do {
					read(mesa[0][RD], &c, 1);
				} while (c == PONG);
				++pong;
			}
			break;
		default: 
			// padre
			signal(SIGALRM, show_ping);
			alarm(1);
			while (true)
			{
				char c;
				write(mesa[0][WR], &PING, 1);
				do {
					read(mesa[1][RD], &c, 1);
				} while (c == PING);
				++ping;
			}
			wait(nullptr);
			break;
	}
}
