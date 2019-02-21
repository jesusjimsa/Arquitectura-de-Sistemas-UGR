//---------------------------------------------------------
// ping.pong.socket.cc
//---------------------------------------------------------

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>

#include <atomic>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <thread>

//---------------------------------------------------------

using namespace std::chrono_literals;

//---------------------------------------------------------

const char PING = '1', PONG = '0';

//---------------------------------------------------------

#define CHECK(x) if ((x) == -1) { std::cout << __FILE__ << ":" << __LINE__ << " --> " << strerror(errno) << std::endl; exit(1); }

//---------------------------------------------------------

int main()
{
	int ping = 0, pong = 0;
	std::atomic<bool> end(false);
	struct sockaddr_in client_address, server_address = {AF_INET, htons(2222), INADDR_ANY, 0};

	std::thread server([&]
	{
		int fd;
		CHECK(fd = socket(PF_INET, SOCK_STREAM, 0));
		
		int one = 1;
		CHECK(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)));
		CHECK(setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one)));
		
		CHECK(bind(fd, (struct sockaddr *)&server_address, sizeof(server_address)));
		
		CHECK(listen(fd, 1));
		
		socklen_t length;
		CHECK(fd = accept(fd, (struct sockaddr *)&client_address, &length));
		
		char c;
		while (!end)
		{
			CHECK(read(fd, &c, 1));
			assert(c == PING);
			CHECK(write(fd, &PONG, 1));
			++ping;
		}
		
		close(fd);
	});
	
	std::thread client([&]
	{
		int fd;
		CHECK(fd = socket(PF_INET, SOCK_STREAM, 0));
		
		CHECK(connect(fd, (struct sockaddr *)&server_address, sizeof(server_address)));
		
		char c;
		while(!end)
		{
			CHECK(write(fd, &PING, 1));
			CHECK(read(fd, &c, 1));
			assert(c == PONG);
			++pong;
		}
		CHECK(write(fd, &PING, 1)); // avoid server lock
		close(fd);
	});
	
	std::this_thread::sleep_for(1s);
	end = true;
	
	server.join();
	client.join();
	
	std::cout << "ping = " << ping << std::endl
	          << "pong = " << pong << std::endl;
}

//---------------------------------------------------------

