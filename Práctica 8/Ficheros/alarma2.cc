#include <unistd.h>    // alarm
#include <chrono>      // now
#include <csignal>     // signal
#include <iostream>    // cout endl
#include <thread>      // this_thread

using namespace std::chrono_literals;

void alarma(int)
{
	std::cout << "alarma" << std::endl;
}

int main()
{
	alarm(1);                          // 1s
	signal(SIGALRM, alarma);

	std::cout << "hola" << std::endl;
	std::this_thread::sleep_for(2s);   // 2s
	std::cout << "adios" << std::endl;
}
