extern void db_log(const char *msg);
static kk_unit_t kk_dbsdk_db_log(kk_string_t msg, kk_context_t *ctx) {
  kk_ssize_t len;
  const uint8_t *cstr = kk_string_buf_borrow(msg, &len, ctx);
  db_log((const char*)cstr);
  kk_string_drop(msg, ctx);
  return kk_Unit;
}