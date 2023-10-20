#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include "Client.h"

using namespace std;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char** argv)
{
	LOG_INFO << "pid = " << getpid();
	if (argc > 1)
	{
		EventLoop loop;
		InetAddress serverAddr(argv[1], stoi(argv[2]));

		Client client(&loop, serverAddr);
		client.connect();
		loop.loop();
	}
	else
	{
		printf("Usage: %s <host_ip> <host_port>\n", argv[0]);
	}
	return 0;
}
