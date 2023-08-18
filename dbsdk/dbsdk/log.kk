module dbsdk/log

extern import
  c file "log-inline.c"

extern dbsdk-db-log(msg: string): console ()
  c "kk_dbsdk_db_log"

pub fun db-log(msg: string): console ()
  dbsdk-db-log(msg)