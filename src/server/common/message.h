#pragma once
#include "global.h"
#include <cstdarg>
#include <cstdint>
class Message;

enum class MessageLevel : int
{
	DEBUG = 0,
	LOG,
	NOTICE,
	WARNING,
	ERROR
};

void MessageHandler(int msg_level, const char *format, ...);

#define DEBUG_MSG(...) MessageHandler(MessageLevel::DEBUG, __VA_ARGS__)

#define LOG_MSG(...) MessageHandler(MessageLevel::LOG, __VA_ARGS__)

#define NOTICE_MSG(...) MessageHandler(MessageLevel::NOTICE, __VA_ARGS__)

#define WARNING_MSG(...) MessageHandler(MessageLevel::WARNING, __VA_ARGS__)

#define ERROR_MSG(...) MessageHandler(MessageLevel::ERROR, __VA_ARGS__)
