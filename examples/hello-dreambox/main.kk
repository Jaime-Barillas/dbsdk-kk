import dbsdk/dbsdk
import dbsdk/log
import dbsdk/clock // Currently needed for Wasm patching to succeed.

fun main()
  db-log("Hello, from Koka!")
  val ts = clock-getTimestamp() // Currently needed for Wasm patching to succeed.
  db-log("TIMESTAMP: " ++ ts.show) // Might as well print the time since we have it.
  return ()