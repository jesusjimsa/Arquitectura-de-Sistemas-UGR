#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
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

int main(int argc, char *argv[])
{
	const char PING = '1', PONG = '2';

	int msgid = msgget(ftok(argv[0], 'x'), IPC_CREAT | 0600);

	struct msgbuf msg;

	switch(fork())
	{
		case -1: 
			// fallo
			std::cout << "fallo en fork()!" << std::endl; 
			exit(EXIT_FAILURE); 
			break;
		case  0:
			// hijo
			signal(SIGALRM, show_pong);
			alarm(1);
			while (true)
			{
				do
					msgrcv(msgid, &msg, 1, PING, MSG_NOERROR);
				while (msg.mtext[0] == PONG);
				msg = {PONG, PONG};
				msgsnd(msgid, &msg, 1, IPC_NOWAIT);
				++pong;
			}
			break;
		default: 
			// padre
			signal(SIGALRM, show_ping);
			alarm(1);
			while (true)
			{
				msg = {PING, PING};
				msgsnd(msgid, &msg, 1, IPC_NOWAIT);
				do
					msgrcv(msgid, &msg, 1, PONG, MSG_NOERROR);
				while (msg.mtext[0] == PING);
				++ping;
			}
			wait(nullptr);
			break;
	}
}
