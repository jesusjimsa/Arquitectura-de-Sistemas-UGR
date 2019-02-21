#include <unistd.h>    // alarm
#include <chrono>      // now
#include <csignal>     // signal raise
#include <cstring>     // strsignal
#include <iostream>    // cout endl

template<int __s, void(__f)(int)> class signal_handler
{
public:
	 signal_handler() { signal(__s,     __f); }
	~signal_handler() { signal(__s, SIG_DFL); }
};

void f(int s)
{
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	std::cout << strsignal(s) << " --> " << std::ctime(&time) << std::flush;
}

int main(int argc, char* argv[])
{
	int DIE = 5;

	signal_handler<SIGINT , f> sigint;
	signal_handler<SIGUSR1, f> sigusr1;

	alarm(DIE); // signal after DIE seconds
	std::cout << "I will die in " << DIE << " seconds :(" << std::endl;

	for(;;)
	{
		sleep(1);
		raise(SIGUSR1);
	}
}
