#include "logging.h"

int LOG_ERROR(const char*error)
{
    return printf(RED"[ %s ]: ERROR: %s\n"rst, PROG_NAME, error);
}

int LOG_DEBUG(const char*msg)
{
    return printf(YELLOW"[ %s ]: WARNING: %s\n"rst, PROG_NAME, msg);
}

int LOG_INFO(const char*info)
{
    return printf(GREEN"[ %s ]: INFO: %s\n"rst, PROG_NAME, info);
}