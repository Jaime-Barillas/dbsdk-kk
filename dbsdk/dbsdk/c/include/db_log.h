#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Log a string to debug output
/// @param msg The message to log
extern void db_log(const char *msg);

/// @brief Log a formatted string to debug output
/// @param fmt The format string
/// @param ... Arguments to format
void db_logf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif