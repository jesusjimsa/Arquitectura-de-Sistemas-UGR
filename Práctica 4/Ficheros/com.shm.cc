//---------------------------------------------------------
// com.shm.cc
//---------------------------------------------------------

#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cassert>
#include <iostream>

//---------------------------------------------------------

int main()
{
	const int key = ftok("/tmp/com.shm", 3);
	const int size = 100;
	int shmid = shmget(key, size, IPC_CREAT | 0600);
	char *s = nullptr;
	
	assert(shmid != -1);
	
	switch(fork())
	{
		case -1: 
			std::cout << "fallo en fork()!"; break;
		case 0: 
			s = static_cast<char*>(shmat(shmid, nullptr, 0));
			std::cout << "hijo escribiendo : ";
			for (char c = 'a'; c <= 'z'; ++c)
				std::cout << (*s++ = c);
			*s = 0;
			std::cout << std::endl;
			break;
		default:
			int msg;
			wait(&msg);
			s = static_cast<char*>(shmat(shmid, nullptr, 0));
			std::cout << "padre ha recibido: " << s << std::endl;
			break;
	}
}

//---------------------------------------------------------

