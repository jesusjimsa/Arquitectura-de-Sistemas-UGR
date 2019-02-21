//---------------------------------------------------------
// spinlock.cc
//---------------------------------------------------------

#include <unistd.h>  // alarm
#include <atomic>    // atomic
#include <iostream>  // cout endl
#include <mutex>     // mutex
#include <thread>    // thread

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class barrera_t
{
public:
	explicit barrera_t(unsigned count): 
		m_count(count), m_generation(0), m_count_reset_value(count) {}

	void esperar()
	{
		unsigned gen = m_generation;
		
		if (--m_count != 0)
		{
			while ((gen == m_generation) && (m_count != 0))
				std::this_thread::yield();
		}
		else
		{
			if (m_generation.compare_exchange_weak(gen, gen + 1))
			{
				m_count = m_count_reset_value;
			}
		}
	}

private:
	std::atomic<unsigned> m_count;
	std::atomic<unsigned> m_generation;
	unsigned m_count_reset_value;
} barrera(N);

//---------------------------------------------------------

void msg(int yo, const char *txt)
{
	static std::mutex m;
	std::unique_lock<std::mutex> l(m);
	std::cout << yo << ": " << txt << std::endl;
}

//---------------------------------------------------------

void hebra(int yo)
{
	while(true)
	{
		msg(yo, "antes");
		barrera.esperar();
		msg(yo, "después");
	}
}

//---------------------------------------------------------

int main()
{
	alarm(1);
	std::thread t[N];
	for (int i = 0; i < N; ++i) t[i] = std::thread(hebra, i);
	for (auto& i: t) i.join();
}

//---------------------------------------------------------

