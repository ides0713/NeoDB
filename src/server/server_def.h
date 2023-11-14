#pragma once
#include <jsoncpp/json/reader.h>

void ServerInit();
void PrintLogo(int style);

const int SERVER_STATUS_HALT = 0;

class SessionTask
{
public:
	void operator()() const
	{
		printf("session task !!!!!!!");
	};

private:
};

class ServerConfig
{
public:
	ServerConfig();

public:
	static void GenDefaultConfig();

private:
};