//---------------------------------------------------------
// ping.pong.udp.cc
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
	socklen_t client_length = sizeof(client_address), server_length = sizeof(server_address);
	
	std::thread server([&]
	{
		int fd;
		CHECK(fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP));
		
		CHECK(bind(fd, (struct sockaddr *)&server_address, sizeof(server_address)));
		
		char c;
		while (!end)
		{
			CHECK(recvfrom(fd, &c, 1, 0, (struct sockaddr *)&client_address, &client_length));
			assert(c == PING);
			CHECK(sendto(fd, &PONG, 1, 0, (struct sockaddr *)&client_address, client_length));
			++ping;
		}
		CHECK(sendto(fd, &PONG, 1, 0, (struct sockaddr *)&client_address, client_length)); // avoid client lock
		close(fd);
	});
	
	std::thread client([&]
	{
		int fd;
		CHECK(fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP));
		
		char c;
		while(!end)
		{
			CHECK(sendto(fd, &PING, 1, 0, (struct sockaddr *)&server_address, server_length));
			CHECK(recvfrom(fd, &c, 1, 0, (struct sockaddr *)&server_address, &server_length));
			assert(c == PONG);
			++pong;
		}
		CHECK(sendto(fd, &PING, 1, 0, (struct sockaddr *)&server_address, server_length)); // avoid server lock
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

