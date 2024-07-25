#ifndef LOGGING_H
#define LOGGING_H
#define PROG_NAME "miniRT"
#include <stdio.h>

void LOG_ERROR(const char*error);
void LOG_WARN(const char*warn);
void LOG_INFO(const char*info);
#endif // LOGGING_H