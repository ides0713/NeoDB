#include "common/message.h"
#include "cstdio"
class Message
{
};
void MessageHandler(int msg_level, const char *format, ...)
{
    switch (msg_level)
    {
    case MessageLevel::DEBUG:
    case MessageLevel::LOG:
    case MessageLevel::NOTICE:
    case MessageLevel::WARNING:
    case MessageLevel::ERROR:
        break;
    
    default:
        printf("unrecognized message level");
        break;
    }
}