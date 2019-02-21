#include <atomic>
#include <thread>

using namespace std::chrono_literals;

class spinlock
{
public:
	void lock()
	{
		while(flag.test_and_set(std::memory_order_acquire))
			std::this_thread::sleep_for(256us);
	}

	void unlock()
	{
		flag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag flag;
};
