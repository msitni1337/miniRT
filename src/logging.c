#include "logging.h"

void LOG_ERROR(const char*error)
{
    printf("[ %s ]: ERROR: %s\n", PROG_NAME, error);
}

void LOG_WARN(const char*warn)
{
    printf("[ %s ]: WARNING: %s\n", PROG_NAME, warn);
}

void LOG_INFO(const char*info)
{
    printf("[ %s ]: INFO: %s\n", PROG_NAME, info);
}
