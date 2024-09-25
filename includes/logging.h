#ifndef LOGGING_H
#define LOGGING_H
#define PROG_NAME "miniRT"
#include <stdio.h>

#define rst   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

int log_error(const char*error);
int log_debug(const char*msg);
int log_info(const char*info);

#endif // LOGGING_H