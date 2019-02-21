//---------------------------------------------------------
// ping.pong.mq.cc
//---------------------------------------------------------

#include <sys/stat.h>

#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

#include <atomic>
#include <cassert>
#include <cerrno>
#include <iostream>
#include <thread>

//---------------------------------------------------------

using namespace std::chrono_literals;

//---------------------------------------------------------

#define CHECK(x) if ((x) == -1) { std::cout << __FILE__ << ":" << __LINE__ << " --> " << strerror(errno) << std::endl; exit(1); }

//---------------------------------------------------------

const char PING = '1', PONG = '0';

//---------------------------------------------------------

int main()
{
	int ping = 0, pong = 0;
	std::atomic<bool> end(false);

	mqd_t qi, qo;
	struct mq_attr attr = {0, 1, 1, 0};
	CHECK(qi = mq_open("/qi", O_CREAT | O_RDWR, 0600, &attr));
	CHECK(qo = mq_open("/qo", O_CREAT | O_RDWR, 0600, &attr));

	std::thread server([&]
	{
		char c;
		while(!end)
		{
			CHECK(mq_receive(qi, &c, 1, nullptr));
			assert(c == PING);
			CHECK(mq_send(qo, &PONG, 1, 0));
			++pong;
		}
	});

	std::thread client([&]
	{
		char c;
		while(!end)
		{
			CHECK(mq_send(qi, &PING, 1, 0));
			CHECK(mq_receive(qo, &c, 1, nullptr));
			assert(c == PONG);
			++ping;
		}
		CHECK(mq_send(qi, &PING, 1, 0)); // avoid server lock
	});

	std::this_thread::sleep_for(1s);
	end = true;

	server.join();
	client.join();

	mq_close(qi);
	mq_close(qo);
	mq_unlink("/qi");
	mq_unlink("/qo");

	std::cout << "ping = " << ping << std::endl
	          << "pong = " << pong << std::endl;
}

//---------------------------------------------------------

