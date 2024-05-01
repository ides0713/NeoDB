#include "common/neodb_log.h"
#include "common/file_handler.h"

#include <cassert>
#include <cstdio>
#include <cstring>

#define DEFAULT_ERROR_LOG "NLog Handler Error"

const int LOG_BUF_LEN = 512;
const int LOG_TAG_LEN = 10;
const int LOG_WRITE_LEN = LOG_BUF_LEN + LOG_TAG_LEN + 1;

char LOG_BUFFER[LOG_BUF_LEN];
char LOG_WRITE_BUFFER[LOG_WRITE_LEN];

const fs::path NLOG_DIR_PATH = fs::path(PROJECT_RUNTIME_OUTPUT_PATH).append("log");
const fs::path NLOG_FILE_PATH = fs::path(PROJECT_RUNTIME_OUTPUT_PATH).append("log").append("logfile");

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
	memmove(log_, log, len);
	time(&time_);
}

NLog::~NLog()
{
	delete[] log_;
}

void NLogManager::Handle(NLog *log)
{
	memset(LOG_WRITE_BUFFER, 0, LOG_WRITE_LEN);
	snprintf(LOG_WRITE_BUFFER, LOG_WRITE_LEN, "%s %s\n", log->GetLevelTag(), log->GetNLog());

	switch (log->GetLevel())
	{
	case NLogLevel::DEBUG:
	case NLogLevel::LOG:
	case NLogLevel::NOTICE:
	case NLogLevel::WARNING:
	case NLogLevel::ERROR:
	{
		// struct tm *p = localtime(&log->Time());
		// printf("%d/%d/%d %02d:%02d:%02d %s %s\n",
		// 	   1900 + p->tm_year,
		// 	   p->tm_mon,
		// 	   p->tm_mday,
		// 	   p->tm_hour,
		// 	   p->tm_min,
		// 	   p->tm_sec,
		// 	   log->GetLevelTag(),
		// 	   log->GetNLog());
		printf("%s", LOG_WRITE_BUFFER);
	}
	break;
	default:
		// todo error unrecognized log type
		assert(false);
	}

	FileHandler::Write(NLOG_FILE_PATH, LOG_WRITE_BUFFER, strlen(LOG_WRITE_BUFFER), "a");
}

void NLogManager::Release()
{
	// delete obj
}

NLogManager &NLogManager::Instance()
{
	static NLogManager instance;
	return instance;
}

void NLogManager::MakeLogDirectory()
{
	// todo add identify for some thing to divide different part of all logs
	// at least from different client
	if (!fs::exists(NLOG_DIR_PATH))
		fs::create_directory(NLOG_DIR_PATH);
	if (!fs::is_directory(NLOG_DIR_PATH))
	{
		// todo what to do if not directroy file exists -- (idk what will happen if file has same
		// name with dir)
		assert(false);
	}
}

void NLogManager::MakeLogFile()
{
	// todo we use only one logfile called "logfile", as we did not determine how to divide
	if (!fs::exists(NLOG_FILE_PATH))
	{
		FILE *nlog_file = fopen(NLOG_FILE_PATH.c_str(), "w");

		if (nlog_file == nullptr)
		{
			// todo error create nlog file failed
			assert(false);
		}

		fclose(nlog_file);
	}
}

NLogManager::NLogManager()
{
	MakeLogDirectory();
	MakeLogFile();
}