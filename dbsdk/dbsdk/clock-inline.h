kk_box_t kk_dbsdk_clock__alloc_DateTime(kk_context_t*);

kk_unit_t kk_dbsdk_clock__clock_timestampToDatetime(uint64_t, kk_box_t, kk_context_t*);
uint64_t kk_dbsdk_clock__clock_datetimeToTimestamp(kk_box_t, kk_context_t*);

uint16_t kk_dbsdk_clock__DateTime_year(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_clock__DateTime_month(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_clock__DateTime_day(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_clock__DateTime_hour(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_clock__DateTime_minute(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_clock__DateTime_second(kk_box_t, kk_context_t*);