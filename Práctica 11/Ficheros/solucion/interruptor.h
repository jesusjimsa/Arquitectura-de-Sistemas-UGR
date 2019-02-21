//---------------------------------------------------------
// interruptor.h
//---------------------------------------------------------

#include <atomic>
#include <mutex>
#include <thread>

//---------------------------------------------------------

class interruptor
{
public:
	interruptor(): contador(0) {}

	void lock(std::mutex& llave)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (++contador == 1)
			llave.lock();
	}

	void unlock(std::mutex& llave)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (--contador == 0)
			llave.unlock();
	}

private:
	std::atomic<unsigned> contador;
	std::mutex mutex;
};

//---------------------------------------------------------

