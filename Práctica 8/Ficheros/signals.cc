#include <iostream>
#include <signal.h>  // signal SIGALRM
#include <unistd.h>  // alarm
#include <pthread.h>
#include <thread>
#include <csignal>     // signal raise

using namespace std;

thread c, s;

void cliente(int){
	signal(SIGUSR2, cliente);

	cout << "[cliente ]: respuesta recibida\n";
	pthread_kill(s.native_handle(), SIGUSR1);
	cout << "[cliente ]: petición enviada\n";
}

void servidor(int){
	signal(SIGUSR1, servidor);
	
	cout << "[servidor]: petición recibida\n";
	pthread_kill(c.native_handle(), SIGUSR2);
	cout << "[servidor]: respuesta enviada\n";
}

int main(){
	alarm(1);

	s = thread([]{
		signal(SIGUSR1, servidor);
		
		c = thread([]{
			signal(SIGUSR2, cliente);
			cout << "[cliente ]: petición enviada" << endl;
			pthread_kill(s.native_handle(), SIGUSR1);
			this_thread::sleep_for(1s);
		});

		c.join();
	});

	s.join();
}