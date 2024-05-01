#include "server_def.h"
#include "common/file_handler.h"
#include "common/neodb_log.h"
#include "global.h"

#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <unordered_set>

// hard code the possible server config option, change both json and set when do something about
// valid server configs
std::unordered_set<std::string> SERVER_CONFIG_LIST = {"LOGO_STYLE", "SERVER_PORT", "RELEASE_DIR"};

const fs::path CONFIG_FILE_PATH = fs::path(PROJECT_SERVER_PATH).append("server_config.json");

static void PrintLogo(LogoStyle style = LogoStyle::BIG);

static void PrintLogo(LogoStyle style)
{
	switch (style)
	{
	case LogoStyle::ALPHA:
		printf("          _____                    _____                     _____                 "
			   "  _____                    _____   \n"
			   "         /\\    \\                  /\\    \\                 /::\\    \\          "
			   "       /\\    \\                  /\\    \\      \n"
			   "        /::\\____\\                /::\\    \\               /::::\\    \\         "
			   "      /::\\    \\                /::\\    \\       \n"
			   "       /::::|   |               /::::\\    \\             /::::::\\    \\          "
			   "   /::::\\    \\              /::::\\    \\       \n"
			   "      /:::::|   |              /::::::\\    \\           /::::::::\\    \\         "
			   "  /::::::\\    \\            /::::::\\    \\      \n"
			   "     /::::::|   |             /:::/\\:::\\    \\         /:::/~~\\:::\\    \\      "
			   "   /:::/\\:::\\    \\          /:::/\\:::\\    \\   \n"
			   "    /:::/|::|   |            /:::/__\\:::\\    \\       /:::/    \\:::\\    \\     "
			   "  /:::/  \\:::\\    \\        /:::/__\\:::\\    \\    \n"
			   "   /:::/ |::|   |           /::::\\   \\:::\\    \\     /:::/    / \\:::\\    \\   "
			   "  /:::/    \\:::\\    \\      /::::\\   \\:::\\    \\   \n"
			   "  /:::/  |::|   | _____    /::::::\\   \\:::\\    \\   /:::/____/   \\:::\\____\\  "
			   " /:::/    / \\:::\\    \\    /::::::\\   \\:::\\    \\  \n"
			   " /:::/   |::|   |/\\    \\  /:::/\\:::\\   \\:::\\    \\ |:::|    |     |:::|    | "
			   "/:::/    /   \\:::\\ ___\\  /:::/\\:::\\   \\:::\\ ___\\ \n"
			   "/:: /    |::|   /::\\____\\/:::/__\\:::\\   \\:::\\____\\|:::|____|     |:::|    "
			   "|/:::/____/     \\:::|    |/:::/__\\:::\\   \\:::|    |\n"
			   "\\::/    /|::|  /:::/    /\\:::\\   \\:::\\   \\::/    / \\:::\\    \\   /:::/    "
			   "/ \\:::\\    \\     /:::|____|\\:::\\   \\:::\\  /:::|____|\n"
			   " \\/____/ |::| /:::/    /  \\:::\\   \\:::\\   \\/____/   \\:::\\    \\ /:::/    / "
			   "  \\:::\\    \\   /:::/    /  \\:::\\   \\:::\\/:::/    / \n"
			   "         |::|/:::/    /    \\:::\\   \\:::\\    \\        \\:::\\    /:::/    /    "
			   " \\:::\\    \\ /:::/    /    \\:::\\   \\::::::/    /  \n"
			   "         |::::::/    /      \\:::\\   \\:::\\____\\        \\:::\\__/:::/    /     "
			   "  \\:::\\    /:::/    /      \\:::\\   \\::::/    /   \n"
			   "         |:::::/    /        \\:::\\   \\::/    /         \\::::::::/    /         "
			   "\\:::\\  /:::/    /        \\:::\\  /:::/    /    \n"
			   "         |::::/    /          \\:::\\   \\/____/           \\::::::/    /          "
			   " \\:::\\/:::/    /          \\:::\\/:::/    /     \n"
			   "         /:::/    /            \\:::\\    \\                \\::::/    /           "
			   "  \\::::::/    /            \\::::::/    /      \n"
			   "        /:::/    /              \\:::\\____\\                \\::/____/            "
			   "   \\::::/    /              \\::::/    /       \n"
			   "        \\::/    /                \\::/    /                                       "
			   "  \\::/____/                \\::/____/        \n"
			   "         \\/____/                  \\/____/                                        "
			   "                                            \n");
		break;
	case LogoStyle::BIG:
		printf(" _   _            _____  ____   \n"
			   "| \\ | |          |  __ \\|  _ \\  \n"
			   "|  \\| | ___  ___ | |  | | |_) | \n"
			   "| . ` |/ _ \\/ _ \\| |  | |  _ <  \n"
			   "| |\\  |  __/ (_) | |__| | |_) | \n"
			   "|_| \\_|\\___|\\___/|_____/|____/  \n");
		break;
	default:
		// todo error
		assert(false);
	}
}

void ServerInit(ServerConfig *configs)
{
	ConfigValue logo_config = configs->GetConfig("LOGO_STYLE");
	PrintLogo((LogoStyle)(*(int *)(logo_config.GetValue())));
	(void)NLogManager::Instance();
}

void ServerRelease(ServerConfig *configs)
{
	NLogManager::Instance().Release();
	delete configs;
	configs = nullptr;
}

ConfigValue::ConfigValue()
{
	type_ = ConfigValueType::INVALID;
	value_ = nullptr;
	size_ = 0;
}

ConfigValue::ConfigValue(ConfigValueType value_type, std::string config_value)
{
	type_ = value_type;
	value_ = nullptr;
	size_ = 0;

	switch (type_)
	{
	case ConfigValueType::INT:
	{
		int value = atoi(config_value.c_str());
		size_ = sizeof(int);
		value_ = new char[size_]{};
		memmove(value_, &value, size_);
	}
	break;
	case ConfigValueType::STRING:
	{
		size_ = config_value.length();
		value_ = new char[size_]{};
		memmove(value_, config_value.c_str(), size_);
	}
	break;
	default:
		// todo error
		assert(false);
	}
}

ConfigValue::ConfigValue(ConfigValueType value_type, const char *config_value)
{
	type_ = value_type;
	switch (type_)
	{
	case ConfigValueType::INT:
	{
		int value = atoi(config_value);
		size_ = sizeof(int);
		value_ = new char[size_]{};
		memmove(value_, &value, size_);
	}
	break;
	case ConfigValueType::STRING:
	{
		size_ = strlen(config_value);
		value_ = new char[size_]{};
		memmove(value_, config_value, size_);
	}
	break;
	default:
		// todo error
		assert(false);
	}
}

ConfigValue::ConfigValue(const ConfigValue &config)
{
	this->type_ = config.type_;
	if (this->type_ == ConfigValueType::INVALID)
	{
		this->value_ = nullptr;
		this->size_ = 0;
	}
	else
	{
		this->size_ = config.size_;
		this->value_ = new char[this->size_];
		memmove(this->value_, config.value_, this->size_);
	}
}

ConfigValue::~ConfigValue()
{
	if (value_)
	{
		delete[] value_;
		value_ = nullptr;
	}
}

bool ConfigValue::equal(const ConfigValue &config)
{
	if (this->type_ == config.type_)
	{
		if (this->type_ == ConfigValueType::INVALID)
			return true;
		else if (this->type_ == ConfigValueType::INT)
		{
			int larg = *reinterpret_cast<int *>(this->value_);
			int rarg = *reinterpret_cast<int *>(config.value_);
			return larg == rarg;
		}
		else if (this->type_ == ConfigValueType::STRING)
		{
			if (this->size_ != config.size_)
				return false;
			else
				return strncmp(this->value_, config.value_, this->size_) == 0;
		}
	}

	return false;
}

bool ConfigValue::equal(std::string str)
{
	if (this->type_ == ConfigValueType::STRING)
	{
		if (this->size_ != str.length())
			return false;
		else
			return strncmp(this->value_, str.c_str(), this->size_) == 0;
	}

	return false;
}

bool ConfigValue::equal(int value)
{
	if (this->type_ == ConfigValueType::INT)
	{
		int larg = *(int *)(this->value_);
		return larg == value;
	}
	return false;
}

bool ConfigValue::equal(const char *str)
{
	if (this->type_ == ConfigValueType::STRING)
	{
		if (this->size_ != strlen(str))
			return false;
		else
			return strncmp(this->value_, str, this->size_) == 0;
	}
	return false;
}

// 1. read from config file(if not exists, create one)
// 2. replace some of config options with user's input
// 3. these configs will be changed by users' commands after server init
ServerConfig::ServerConfig(int argc, char *argv[])
{
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	GenDefaultConfig();
	std::ifstream server_config_file(CONFIG_FILE_PATH);
	Json::Value json_values;

	if (!Json::parseFromStream(builder, server_config_file, &json_values, &errs))
	{
		// todo error
		std::cout << "Error parsing JSON(config values): " << errs << std::endl;
		return;
	}

	// hard code here
	Json::Value::Members mem = json_values.getMemberNames();

	for (auto it = json_values.begin(); it != json_values.end(); it++)
	{
		std::string key = std::string(it.key().asString().c_str());
		const Json::String &type = (*it)["type"].asString(), &value = (*it)["value"].asString();
		ConfigValue *val = nullptr;

		if (SERVER_CONFIG_LIST.find(key) == SERVER_CONFIG_LIST.end())
		{
			// todo error
			assert(false);
		}

		if (type == "int")
		{
			const char *cstr_val = value.c_str();
			val = new ConfigValue(ConfigValueType::INT, cstr_val);
		}
		else if (type == "string")
		{
			// as char * form by json::string not ended with a '\0'
			std::string str = std::string(value);
			val = new ConfigValue(ConfigValueType::STRING, str);
		}

		if (configs_.find(std::string(key)) != configs_.end())
		{
			// todo error
			assert(false);
		}

		configs_.emplace(std::string(key), val);
	}
}

void ServerConfig::GenDefaultConfig()
{
	// todo determine how to gen default config file
}

ConfigValue ServerConfig::GetConfig(std::string config_name)
{
	if (configs_.find(config_name) != configs_.end())
		return *(configs_[config_name]);
	return ConfigValue();
}

ServerConfig::~ServerConfig()
{
	for (auto it = configs_.begin(); it != configs_.end();)
	{
		delete it->second;
		it->second = nullptr;
		configs_.erase(it++);
	}
}

void ServerSessionTask::operator()()
{
	sometest();
}

void ServerSessionTask::sometest()
{
	// nlog
	NLOG_DEBUG("%d", 12);
	NLOG_ERROR("%d", 34);
	NLOG_LOG("%d", 56);
	NLOG_NOTICE("%d", 78);
	NLOG_WARNING("%d", 910);
}