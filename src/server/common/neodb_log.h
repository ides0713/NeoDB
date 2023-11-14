#pragma once

#include "global.h"
#include <cstdarg>
#include <ctime>
enum class NLogLevel : int
{
	DEBUG = 0,
	LOG,
	NOTICE,
	WARNING,
	ERROR
};

const char *LevelTag(NLogLevel level);

void NeoDBLog(NLogLevel log_level, const char *format, ...);

#define NLOG_DEBUG(...) NeoDBLog(NLogLevel::DEBUG, ##__VA_ARGS__)

#define NLOG_LOG(...) NeoDBLog(NLogLevel::LOG, __VA_ARGS__)

#define NLOG_NOTICE(...) NeoDBLog(NLogLevel::NOTICE, __VA_ARGS__)

#define NLOG_WARNING(...) NeoDBLog(NLogLevel::WARNING, __VA_ARGS__)

#define NLOG_ERROR(...) NeoDBLog(NLogLevel::ERROR, __VA_ARGS__)

// TODO: NLog内部需要有一个类似消息队列的系统进行并发控制, 为了达到这一目的,
// 可能需要引入NLog的编号或者加入一个时间戳用于标识消息顺序先后
class NLog
{
public:
	NLog(NLogLevel level, const char *log, int len);
	~NLog();
	NLogLevel GetLevel() const
	{
		return level_;
	}

	const char *GetNLog() const
	{
		return log_;
	}

	time_t &Time()
	{
		return time_;
	}

	time_t GetTime() const
	{
		return time_;
	}

	const char *GetLevelTag()
	{
		return LevelTag(level_);
	}

private:
	NLogLevel level_;
	char *log_;
	time_t time_;
};

class NLogManager
{
public:
	NLogManager(const NLogManager &another) = delete;
	NLogManager &operator=(const NLogManager &another) = delete;
	static NLogManager &Instance()
	{
		static NLogManager instance;
		return instance;
	}
	void Handle(NLog *log);

private:
	NLogManager() = default;
};