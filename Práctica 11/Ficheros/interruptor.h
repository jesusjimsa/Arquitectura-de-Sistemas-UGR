//---------------------------------------------------------
// interruptor.h
//---------------------------------------------------------

#include <atomic>
#include <mutex>
#include <thread>

using namespace std;

//---------------------------------------------------------

class interruptor{
public:
	interruptor(): contador(0) {}

	void lock(mutex& llave){
		lock_guard<mutex> lock(mtx);
		
		if (++contador == 1){
			llave.lock();
		}
	}

	void unlock(mutex& llave){
		lock_guard<mutex> lock(mtx);
		
		if (--contador == 0){
			llave.unlock();
		}
	}

private:
	atomic<unsigned> contador;
	mutex mtx;
};

//---------------------------------------------------------
