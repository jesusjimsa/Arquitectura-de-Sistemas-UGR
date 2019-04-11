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
	this_thread::sleep_for(1s);
}

void servidor(int){
	signal(SIGUSR1, servidor);
	cout << "[servidor]: petición recibida\n";
	pthread_kill(c.native_handle(), SIGUSR2);
	cout << "[servidor]: respuesta enviada\n";
	this_thread::sleep_for(1s);
}

int main(){
	alarm(1);

	signal(SIGUSR2, cliente);
	signal(SIGUSR1, servidor);

	c = thread(cliente, SIGUSR2);
	s = thread(servidor, SIGUSR1);

	c.join();
	s.join();
}