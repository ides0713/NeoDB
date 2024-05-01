#pragma once

#include <cstring>
#include <map>
#include <string>

enum class LogoStyle
{
	ALPHA = 0,
	BIG
};

enum class ConfigValueType
{
	INVALID = 0,
	INT,
	STRING
};

enum class ServerStatus
{
	HALT = 0,
};

class ConfigValue
{
public:
	ConfigValue();
	ConfigValue(ConfigValueType value_type, std::string config_value);
	ConfigValue(ConfigValueType value_type, const char *config_value);
	ConfigValue(const ConfigValue &config);
	~ConfigValue();

	ConfigValueType GetType() const
	{
		return type_;
	}

	const char *GetValue()
	{
		return value_;
	}

	int GetSize() const
	{
		return size_;
	}

	bool equal(const ConfigValue &config);
	bool equal(std::string str);
	bool equal(const char *str);
	bool equal(int value);

private:
	ConfigValueType type_;
	char *value_;
	int size_;
};

class ServerSessionTask
{
public:
	void operator()();

private:
	void sometest();
};

class ServerConfig
{
public:
	ServerConfig(int argc, char *argv[]);
	~ServerConfig();

	ConfigValue GetConfig(std::string config_name);

private:
	static void GenDefaultConfig();

private:
	std::map<std::string, ConfigValue *> configs_;
};

void ServerInit(ServerConfig *configs);
void ServerRelease(ServerConfig *configs);