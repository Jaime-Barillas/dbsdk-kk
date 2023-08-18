module dbsdk/clock

import std/num/int64

extern import
  c file "clock-inline.h"

extern dbsdk-clock-getTimestamp(): ndet int64
  c "clock_getTimestamp"

pub fun clock-getTimestamp(): ndet int
  dbsdk-clock-getTimestamp().uint