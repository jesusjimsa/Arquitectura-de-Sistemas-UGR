#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

int main(){
    int key = ftok("/tmp/sol.com.shm", 3);
	int shmid = shmget(key, 100, IPC_CREAT | 0600);
	char *data = nullptr;

	switch(fork()){
		case -1:
			cout << "Fallo en fork()!";

			break;
		case 0:
			data = static_cast<char*>(shmat(shmid, nullptr, 0));
			
			*data = 'p';

			break;
		default:
			wait(nullptr);	// Espera a que el hijo acabe su ejecución

			data = static_cast<char*>(shmat(shmid, nullptr, 0));
			
			cout << "Recibido por el padre: " << data << endl;
			
			break;
	}

	/* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
}