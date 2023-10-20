#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include "Server.h"

using namespace std;

bool parseArguments(int argc, char** argv)
{
	if (argc != 2)
		return false;
	return true;
}

int main(int argc, char** argv)
{
	if (!parseArguments(argc, argv))
	{
		cout << "Usage:\n" 
			<< argv[0] << " <port>\n";
		return -1;
	}
	LOG_INFO << "pid = " << getpid();
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(stoi(argv[1]));
	Server server(&loop, listenAddr);
	server.start();
	loop.loop();
	return 0;
}

