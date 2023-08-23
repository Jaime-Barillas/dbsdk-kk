import dbsdk/dbsdk
import dbsdk/log
import dbsdk/clock

fun main()
  db-log("Test db_clock")
  db-log("=============")
  db-log("")

  val ts = get-timestamp()
  db-log("get-timestamp(): " ++ ts.show)

  db-log("")
  db-log("alloc-dateTime() - Not printing result")
  val dt = alloc-dateTime()

  db-log("timestamp-to-dateTime() - Not printing result")
  timestamp-to-dateTime(ts, dt)
  db-log("")

  db-log("dateTime-to-timestamp(): " ++ dateTime-to-timestamp(dt).show)

  db-log("year(): "   ++ dt.year.show)
  db-log("month(): "  ++ dt.month.show)
  db-log("day(): "    ++ dt.day.show)
  db-log("hour(): "   ++ dt.hour.show)
  db-log("minute(): " ++ dt.minute.show)
  db-log("second(): " ++ dt.second.show)

  db-log("")
  db-log("Test db_clock End")
  db-log("=================")
  return ()
