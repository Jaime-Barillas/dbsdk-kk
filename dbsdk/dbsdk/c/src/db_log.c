#include <stdio.h>
#include <stdarg.h>
#include "db_log.h"

void db_logf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buf[1024];
    vsprintf(buf, fmt, args);

    db_log(buf);

    va_end(args);
}