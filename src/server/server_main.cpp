#include "global.h"
#include "server_def.h"
#include <cstdio>
#include <thread>

int main(int argc, char* argv[])
{
	ServerInit();
	while (true)
	{
	}
	return SERVER_STATUS_HALT;
}