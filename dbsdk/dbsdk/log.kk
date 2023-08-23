module dbsdk/log

extern import
  c header-file "c/include/db_log.h"

extern import
  c file "log-inline"

inline extern dbsdk-db-log(msg: string): console ()
  c "kk_dbsdk_log__db_log"

inline extern dbsdk-db-logf(fmt: string, vargs: list<any>): console ()
  c "kk_dbsdk_log__db_logf"

pub fun db-log(msg: string): console ()
  dbsdk-db-log(msg)

// TODO: Implement
fun db-logf(fmt: string, args: list<any>): console ()
  dbsdk-db-logf(fmt, args)