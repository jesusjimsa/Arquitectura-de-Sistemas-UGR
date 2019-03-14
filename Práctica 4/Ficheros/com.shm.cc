//---------------------------------------------------------
// com.shm.cc
//---------------------------------------------------------

#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <iostream>

//---------------------------------------------------------

int main()
{
	int key = ftok("/tmp/com.shm", 3);
	int shmid = shmget(key, 100, IPC_CREAT | 0600);
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
			wait(nullptr);
			s = static_cast<char*>(shmat(shmid, nullptr, 0));
			std::cout << "padre ha recibido: " << s << std::endl;
			break;
	}
}

//---------------------------------------------------------

