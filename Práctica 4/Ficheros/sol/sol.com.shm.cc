#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

int main(){
    int key = ftok("tmp/com.shm", 3);
	int shmid = shmget(key, 100, 0600 | IPC_CREAT);
	char *data = nullptr;

	switch(fork()){
		case -1:
			cout << "Fallo en fork()!";

			break;
		case 0:
			data = static_cast<char*>(shmat(shmid, nullptr, 0));
			data = "mensajito";

			break;
		default:
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