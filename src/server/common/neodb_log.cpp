#include "common/neodb_log.h"
#include <cstdio>
#include <cstring>

#define DEFAULT_ERROR_LOG "NLog Handler Error"

const int LOG_BUF_LEN = 512;
char LOG_BUFFER[LOG_BUF_LEN];

const char *LevelTag(NLogLevel level)
{
	switch (level)
	{
	case NLogLevel::DEBUG:
		return "[DEBUG]";
	case NLogLevel::LOG:
		return "[LOG]";
	case NLogLevel::NOTICE:
		return "[NOTICE]";
	case NLogLevel::WARNING:
		return "[WARNING]";
	case NLogLevel::ERROR:
		return "[ERROR]";
	default:
		return nullptr;
	}
}

void NeoDBLog(NLogLevel nlog_level, const char *format, ...)
{
	switch (nlog_level)
	{
	case NLogLevel::DEBUG:
	case NLogLevel::LOG:
	case NLogLevel::NOTICE:
	case NLogLevel::WARNING:
	case NLogLevel::ERROR:
	{
		va_list var_list;
		va_start(var_list, format);
		int ret = vsprintf(LOG_BUFFER, format, var_list);
		va_end(var_list);
		NLog *m = new NLog(static_cast<NLogLevel>(nlog_level), LOG_BUFFER, ret);
		// MessageManager::Instance().SetXId(m);
		NLogManager::Instance().Handle(m);
	}
	break;
	default:
		strlen(DEFAULT_ERROR_LOG);
		NLog *m = new NLog(NLogLevel::ERROR, DEFAULT_ERROR_LOG, strlen(DEFAULT_ERROR_LOG));
		// MessageManager::Instance();
		NLogManager::Instance().Handle(m);
		break;
	}
}

NLog::NLog(NLogLevel level, const char *log, int len)
{
	level_ = level;
	log_ = new char[len + 1];
	memset(log_, 0, len + 1);
	strncpy(log_, log, len);
	time(&time_);
}

NLog::~NLog()
{
	delete[] log_;
}

void NLogManager::Handle(NLog *log)
{
	{
		switch (log->GetLevel())
		{
		case NLogLevel::DEBUG:
		case NLogLevel::LOG:
		case NLogLevel::NOTICE:
		case NLogLevel::WARNING:
		case NLogLevel::ERROR:
		{
			struct tm *p = localtime(&log->Time());
			printf("%d/%d/%d %02d:%02d:%02d %s %s\n",
				   1900 + p->tm_year,
				   p->tm_mon,
				   p->tm_mday,
				   p->tm_hour,
				   p->tm_min,
				   p->tm_sec,
				   log->GetLevelTag(),
				   log->GetNLog());
		}
		break;
		default:
			break;
		}
	}
}