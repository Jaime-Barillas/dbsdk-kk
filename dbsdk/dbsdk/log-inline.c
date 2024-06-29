kk_unit_t kk_dbsdk_log__db_log(kk_string_t msg, kk_context_t *ctx) {
  kk_ssize_t len;
  const uint8_t *cstr = kk_string_buf_borrow(msg, &len, ctx);
  db_log((const char*)cstr);
  kk_string_drop(msg, ctx);
  return kk_Unit;
}

kk_unit_t kk_dbsdk_log__db_logf(kk_string_t fmt, kk_std_core_types__list vargs, kk_context_t *ctx) {
  // TODO: Reimplement db_logf? That could maybe be done in Koka.
  return kk_Unit;
}
