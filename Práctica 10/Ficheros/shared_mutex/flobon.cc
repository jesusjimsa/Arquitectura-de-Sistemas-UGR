//---------------------------------------------------------
// flobon.cc
//---------------------------------------------------------

#include <unistd.h>            // alarm
#include <algorithm>           // for_each
#include <condition_variable>  // condition_variable
#include <iostream>            // cout endl
#include <mutex>               // mutex lock_guard unique_lock
#include <sstream>             // stringstream
#include <string>              // string
#include <thread>              // thread
#include <shared_mutex>

//---------------------------------------------------------

const int N = 32;

//---------------------------------------------------------

class ThreadSafeCounter {
 public:
  ThreadSafeCounter() = default;
 
  // Multiple threads/readers can read the counter's value at the same time.
  unsigned int get() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return value_;
  }
 
  // Only one thread/writer can increment/write the counter's value.
  void increment() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_++;
  }
 
  // Only one thread/writer can reset/write the counter's value.
  void reset() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_ = 0;
  }
 
 private:
  mutable std::shared_mutex mutex_;
  unsigned int value_ = 0;
};

class barrera_t
{
public:
	explicit barrera_t(unsigned _limite):
		limite(_limite) {}

	void esperar()
	{
    std::unique_lock<std::mutex> lock(m);
		contador.increment();
		if (contador.get() < limite)
		{
			restart.wait(lock);
		}
		else
		{
      contador.reset();
			restart.notify_all();
		}
	}

private:
	unsigned limite;
  std::mutex m;
	std::condition_variable restart;
  ThreadSafeCounter contador;  
} barrera(N);

//---------------------------------------------------------

void hebra(int yo)
{
	std::string   antes = std::to_string(yo) +   ": antes\n", 
	            despues = std::to_string(yo) + ": después\n";
	while(true)
	{
		std::cout << antes;
		barrera.esperar();
		std::cout << despues;
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

