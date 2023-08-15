#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Represents date & time values for display
typedef struct
{
    /// @brief The year
    uint16_t year;

    /// @brief The month (1..12)
    uint8_t month;

    /// @brief The day of the month (1..31)
    uint8_t day;

    /// @brief The hour of the day (0..23)
    uint8_t hour;

    /// @brief The minute of the hour (0..59)
    uint8_t minute;

    /// @brief The second of the minute (0..59)
    uint8_t second;
} clock_DateTime;

/// @brief Get the current timestamp
/// @return A timestamp representing the current time as number of seconds since January 1st, 1970
uint64_t clock_getTimestamp();

/// @brief Convert a timestamp to a datetime
/// @param timestamp The timestamp to convert
/// @param dateTime Pointer to a datetime struct to write
void clock_timestampToDatetime(uint64_t timestamp, clock_DateTime *dateTime);

/// @brief Convert a datetime to a timestamp
/// @param dateTime Pointer to the datetime to convert
/// @return A timestamp representing the given datetime as a number of seconds since January 1st, 1970
uint64_t clock_datetimeToTimestamp(const clock_DateTime *dateTime);

#ifdef __cplusplus
}
#endif