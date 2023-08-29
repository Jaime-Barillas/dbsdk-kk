kk_unit_t kk_dbsdk_vdp__vdp_clearColor(kk_box_t, kk_context_t*);

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

kk_unit_t kk_dbsdk_vdp__vdp_setVsyncHandler(kk_function_t, kk_context_t*);

kk_box_t kk_dbsdk_vdp__alloc_Color32(uint8_t, uint8_t, uint8_t, uint8_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_r(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_g(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_b(kk_box_t, kk_context_t*);
uint8_t kk_dbsdk_vdp__Color32_a(kk_box_t, kk_context_t*);
kk_unit_t kk_dbsdk_vdp__initialize(kk_box_t, kk_context_t*);