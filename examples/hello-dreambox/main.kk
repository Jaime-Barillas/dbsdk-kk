import dbsdk/dbsdk
import dbsdk/log
import dbsdk/clock

fun main()
  db-log("Hello, from Koka!")
  db-log("TIMESTAMP: " ++ clock-getTimestamp().show)
  return ()