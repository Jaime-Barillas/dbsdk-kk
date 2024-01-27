import dbsdk/dbsdk
import dbsdk/log
import dbsdk/clock

fun main()
  db-log("Hello, from Koka!")
  db-log("TIMESTAMP: " ++ get-timestamp().show)
  return ()