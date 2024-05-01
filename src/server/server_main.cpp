#include "global.h"
#include "server_def.h"
#include <cstdio>
#include <thread>

int main(int argc, char *argv[])
{
	ServerConfig *conf = new ServerConfig(argc, argv);
	ServerInit(conf);

	// TODO: multi-threads(currently a simple mode)
	ServerSessionTask a;
	std::thread yibaminuo(a);
	yibaminuo.join();

	ServerRelease(conf);
	return static_cast<int>(ServerStatus::HALT);
}