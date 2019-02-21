#include <unistd.h>    // alarm
#include <chrono>      // now
#include <csignal>     // signal raise
#include <cstring>     // strsignal
#include <iostream>    // cout endl

class signal_handler
{
public:
	 signal_handler(int _s, void (_f)(int)): s(_s) { signal(s, _f); }
	~signal_handler() { signal(s, SIG_DFL); }

private:
	int s;
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

	signal_handler sigint (SIGINT , f);
	signal_handler sigusr1(SIGUSR1, f);
//	signal_handler sigalrm(SIGALRM, [](int) { exit(1); });

	alarm(DIE); // signal after DIE seconds
	std::cout << "I will die in " << DIE << " seconds :(" << std::endl;

	for(;;)
	{
		sleep(1);
		raise(SIGUSR1);
	}
}
