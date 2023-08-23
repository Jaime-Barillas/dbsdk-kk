static void kk_dbsdk_clock__free_DateTime(void *dt_ptr, kk_block_t *b, kk_context_t *ctx) {
  kk_unused(ctx);
  clock_DateTime *dt = (clock_DateTime*)dt_ptr;
  if (dt != NULL) free(dt);
}

kk_box_t kk_dbsdk_clock__alloc_DateTime(kk_context_t *ctx) {
  clock_DateTime *dt = malloc(sizeof(clock_DateTime));
  return kk_cptr_raw_box(&kk_dbsdk_clock__free_DateTime, dt, ctx);
}

kk_unit_t kk_dbsdk_clock__clock_timestampToDatetime(uint64_t ts, kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  clock_timestampToDatetime(ts, dt);
  kk_box_drop(dt_boxed_ptr, ctx);
  return kk_Unit;
}

uint64_t kk_dbsdk_clock__clock_datetimeToTimestamp(kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  uint64_t ts = clock_datetimeToTimestamp(dt);
  kk_box_drop(dt_boxed_ptr, ctx);
  return ts;
}

uint16_t kk_dbsdk_clock__DateTime_year(kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  uint16_t year = dt->year;
  kk_box_drop(dt_boxed_ptr, ctx);
  return year;
}

uint8_t kk_dbsdk_clock__DateTime_month(kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  uint8_t month = dt->month;
  kk_box_drop(dt_boxed_ptr, ctx);
  return month;
}

uint8_t kk_dbsdk_clock__DateTime_day(kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  uint8_t day = dt->day;
  kk_box_drop(dt_boxed_ptr, ctx);
  return day;
}

uint8_t kk_dbsdk_clock__DateTime_hour(kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  uint8_t hour = dt->hour;
  kk_box_drop(dt_boxed_ptr, ctx);
  return hour;
}

uint8_t kk_dbsdk_clock__DateTime_minute(kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  uint8_t minute = dt->minute;
  kk_box_drop(dt_boxed_ptr, ctx);
  return minute;
}

uint8_t kk_dbsdk_clock__DateTime_second(kk_box_t dt_boxed_ptr, kk_context_t *ctx) {
  clock_DateTime *dt = (clock_DateTime*)kk_cptr_raw_unbox_borrowed(dt_boxed_ptr, ctx);
  uint8_t second = dt->second;
  kk_box_drop(dt_boxed_ptr, ctx);
  return second;
}