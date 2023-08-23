module dbsdk/clock

import std/num/int64

extern import
  c header-file "c/include/db_clock.h"

extern import
  c file "clock-inline"

abstract value struct dateTime(boxed_ptr: any)

inline extern dbsdk-clock-getTimestamp(): ndet int64
  c "clock_getTimestamp"

inline extern dbsdk-clock-timestampToDatetime(ts: int64, dt: any): ()
  c "kk_dbsdk_clock__clock_timestampToDatetime"

inline extern dbsdk-clock-datetimeToTimestamp(dt: any): int64
  c "kk_dbsdk_clock__clock_datetimeToTimestamp"

inline extern dbsdk-clock-alloc-DateTime(): any
  c "kk_dbsdk_clock__alloc_DateTime"

// NOTE: There seems to be no operation to convert a uint16 to an int, only
// int16 to an int. The signedness does not matter as it is unlikely the year
// will hold something over ~32,000 (which would convert to a negative int.)
inline extern dbsdk-clock-DateTime-year(dt: any): int16
  c "kk_dbsdk_clock__DateTime_year"

inline extern dbsdk-clock-DateTime-month(dt: any): int8
  c "kk_dbsdk_clock__DateTime_month"

inline extern dbsdk-clock-DateTime-day(dt: any): int8
  c "kk_dbsdk_clock__DateTime_day"

inline extern dbsdk-clock-DateTime-hour(dt: any): int8
  c "kk_dbsdk_clock__DateTime_hour"

inline extern dbsdk-clock-DateTime-minute(dt: any): int8
  c "kk_dbsdk_clock__DateTime_minute"

inline extern dbsdk-clock-DateTime-second(dt: any): int8
  c "kk_dbsdk_clock__DateTime_second"


pub fun get-timestamp(): ndet int
  dbsdk-clock-getTimestamp().uint()

pub fun timestamp-to-dateTime(timestamp: int, date-time: dateTime)
  dbsdk-clock-timestampToDatetime(timestamp.uint64(), date-time.boxed_ptr)

pub fun dateTime-to-timestamp(date-time: dateTime): int
  dbsdk-clock-datetimeToTimestamp(date-time.boxed_ptr).uint()

pub fun alloc-dateTime(): dateTime
  DateTime(dbsdk-clock-alloc-DateTime())

pub fun year(date-time: dateTime): int
  dbsdk-clock-DateTime-year(date-time.boxed_ptr).int()

pub fun month(date-time: dateTime): int
  dbsdk-clock-DateTime-month(date-time.boxed_ptr).uint()

pub fun day(date-time: dateTime): int
  dbsdk-clock-DateTime-day(date-time.boxed_ptr).uint()

pub fun hour(date-time: dateTime): int
  dbsdk-clock-DateTime-hour(date-time.boxed_ptr).uint()

pub fun minute(date-time: dateTime): int
  dbsdk-clock-DateTime-minute(date-time.boxed_ptr).uint()

pub fun second(date-time: dateTime): int
  dbsdk-clock-DateTime-second(date-time.boxed_ptr).uint()