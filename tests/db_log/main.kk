import dbsdk/dbsdk
import dbsdk/log

fun main()
  db-log("Test db_clock")
  db-log("=============")
  db-log("")

  db-log("DEBUGGING MESSAGE")
  // db-logf("FORMATTED %s", ["MESSAGE"])

  db-log("")
  db-log("Test db_clock End")
  db-log("=================")
  return ()
