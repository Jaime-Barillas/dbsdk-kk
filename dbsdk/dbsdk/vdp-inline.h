kk_unit_t kk_dbsdk_vdp__vdp_clearColor(kk_box_t, kk_context_t*);
kk_unit_t kk_dbsdk_vdp__vdp_setTextureDataRegion(uint32_t, uint32_t, kk_box_t , intptr_t, uint32_t, kk_context_t*);
kk_unit_t kk_dbsdk_vdp__vdp_copyFbToTexture(kk_box_t, kk_box_t, uint32_t, kk_context_t*);
kk_unit_t kk_dbsdk_vdp__vdp_setVsyncHandler(kk_function_t, kk_context_t*);

static inline kk_unit_t dbsdk_vdp__vdp_clearDepth(float depth) {
  vdp_clearDepth(depth);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_depthWrite(uint8_t enable) {
  vdp_depthWrite(enable);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_depthFunc(uint32_t comparison) {
  vdp_depthFunc(comparison);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_blendEquation(uint32_t mode) {
  vdp_blendEquation(mode);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_blendFunc(uint32_t srcFactor, uint32_t dstFactor) {
  vdp_blendFunc(srcFactor, dstFactor);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_setWinding(uint32_t windingOrder) {
  vdp_setWinding(windingOrder);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_setCulling(uint8_t enabled) {
  vdp_setCulling(enabled);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_releaseTexture(uint32_t textureHandle) {
  vdp_releaseTexture(textureHandle);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_setTextureData(uint32_t textureHandle, uint32_t level, intptr_t data, uint32_t dataLen) {
  vdp_setTextureData(textureHandle, level, (const void*) data, dataLen);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_setTextureDataYUV(uint32_t textureHandle, intptr_t yData, uint32_t yDataLen, intptr_t uData, uint32_t uDataLen, intptr_t vData, uint32_t vDataLen) {
  vdp_setTextureDataYUV(textureHandle, (const void*) yData, yDataLen, (const void*) uData, uDataLen, (const void*) vData, vDataLen);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_setSampleParams(uint32_t filter, uint32_t wrapU, uint32_t wrapV) {
  vdp_setSampleParams(filter, wrapU, wrapV);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_bindTexture(uint32_t textureHandle) {
  vdp_bindTexture(textureHandle);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  vdp_viewport(x, y, width, height);
  return kk_Unit;
}
static inline kk_unit_t dbsdk_vdp__vdp_submitDepthQuery(float refVal, uint32_t comparison, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  vdp_submitDepthQuery(refVal, comparison, x, y, width, height);
  return kk_Unit;
}

kk_box_t kk_dbsdk_vdp__alloc_Color32(uint8_t, uint8_t, uint8_t, uint8_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_r(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_g(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_b(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_a(kk_box_t, kk_context_t*);
kk_box_t kk_dbsdk_vdp__alloc_Rect(uint32_t, uint32_t, uint32_t, uint32_t, kk_context_t*);
uint32_t kk_dbsdk_vdp__Rect_x(kk_box_t, kk_context_t*);
uint32_t kk_dbsdk_vdp__Rect_y(kk_box_t, kk_context_t*);
uint32_t kk_dbsdk_vdp__Rect_w(kk_box_t, kk_context_t*);
uint32_t kk_dbsdk_vdp__Rect_h(kk_box_t, kk_context_t*);
kk_unit_t kk_dbsdk_vdp__initialize(kk_box_t, kk_context_t*);