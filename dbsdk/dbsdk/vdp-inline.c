// Work-around so the Koka provided tick function can be sent to
// `vdp_setVsyncHandler` without args and still know which function to call
// with what ctx. `vdp_setVsyncHandler` requires a function that takes no
// arguments and returns void. The workaround
static kk_context_t* KOKA_CTX;
static kk_function_t TICK_FUNCTION;
static kk_box_t CURRENT_STATE;

static void dbsdk_vdp__tick_func(void) {
  CURRENT_STATE = kk_function_call(
    kk_box_t, // ret type.
    (kk_function_t, kk_box_t, kk_context_t*), // fn arg types.
    TICK_FUNCTION, // fn to call.
    (TICK_FUNCTION, CURRENT_STATE, KOKA_CTX), // fn args.
    KOKA_CTX
  );
}



kk_unit_t kk_dbsdk_vdp__vdp_clearColor(kk_box_t color_boxed_ptr, kk_context_t *ctx) {
  vdp_Color32 *color = (vdp_Color32*)kk_cptr_raw_unbox_borrowed(color_boxed_ptr, ctx);
  vdp_clearColor(color);
  kk_box_drop(color_boxed_ptr, ctx);
  return kk_Unit;
}

kk_unit_t kk_dbsdk_vdp__vdp_setTextureDataRegion(uint32_t textureHandle, uint32_t level, kk_box_t dstRect_boxed_ptr, intptr_t data, uint32_t dataLen, kk_context_t *ctx) {
  vdp_Rect *rect = (vdp_Rect*)kk_cptr_raw_unbox_borrowed(dstRect_boxed_ptr, ctx);
  vdp_setTextureDataRegion(textureHandle, level, rect, (const void*)data, dataLen);
  kk_box_drop(dstRect_boxed_ptr, ctx);
  return kk_Unit;
}

kk_unit_t kk_dbsdk_vdp__vdp_copyFbToTexture(kk_box_t srcRect_boxed_ptr, kk_box_t dstRect_boxed_ptr, uint32_t textureHandle, kk_context_t *ctx) {
  vdp_Rect *srcRect = (vdp_Rect*)kk_cptr_raw_unbox_borrowed(srcRect_boxed_ptr, ctx);
  vdp_Rect *dstRect = (vdp_Rect*)kk_cptr_raw_unbox_borrowed(dstRect_boxed_ptr, ctx);
  vdp_copyFbToTexture(srcRect, dstRect, textureHandle);
  kk_box_drop(srcRect_boxed_ptr, ctx);
  kk_box_drop(dstRect_boxed_ptr, ctx);
  return kk_Unit;
}

kk_unit_t kk_dbsdk_vdp__vdp_setVsyncHandler(kk_function_t tick, kk_context_t *ctx) {
  if (!kk_function_is_null(TICK_FUNCTION, ctx)) {
    kk_function_drop(TICK_FUNCTION, ctx);
  }
  kk_function_dup(tick, ctx);
  TICK_FUNCTION = tick;
  vdp_setVsyncHandler(dbsdk_vdp__tick_func);
  return kk_Unit;
}

static void kk_dbsdk_vdp__free_Color32(void *color_ptr, kk_block_t *b, kk_context_t *ctx) {
  kk_unused(ctx);
  vdp_Color32 *color = (vdp_Color32*)color_ptr;
  if (color != NULL) free(color);
}

kk_box_t kk_dbsdk_vdp__alloc_Color32(uint8_t r, uint8_t g, uint8_t b, uint8_t a, kk_context_t *ctx) {
  vdp_Color32 *color = malloc(sizeof(vdp_Color32));
  *color = (vdp_Color32){.r = r, .g = g, .b = b, .a = a};
  return kk_cptr_raw_box(&kk_dbsdk_vdp__free_Color32, color, ctx);
}

uint8_t kk_dbsdk_vdp__Color32_r(kk_box_t color_boxed_ptr, kk_context_t *ctx) {
  vdp_Color32 *color = (vdp_Color32*)kk_cptr_raw_unbox_borrowed(color_boxed_ptr, ctx);
  uint8_t r = color->r;
  kk_box_drop(color_boxed_ptr, ctx);
  return r;
}

uint8_t kk_dbsdk_vdp__Color32_g(kk_box_t color_boxed_ptr, kk_context_t *ctx) {
  vdp_Color32 *color = (vdp_Color32*)kk_cptr_raw_unbox_borrowed(color_boxed_ptr, ctx);
  uint8_t g = color->g;
  kk_box_drop(color_boxed_ptr, ctx);
  return g;
}

uint8_t kk_dbsdk_vdp__Color32_b(kk_box_t color_boxed_ptr, kk_context_t *ctx) {
  vdp_Color32 *color = (vdp_Color32*)kk_cptr_raw_unbox_borrowed(color_boxed_ptr, ctx);
  uint8_t b = color->b;
  kk_box_drop(color_boxed_ptr, ctx);
  return b;
}

uint8_t kk_dbsdk_vdp__Color32_a(kk_box_t color_boxed_ptr, kk_context_t *ctx) {
  vdp_Color32 *color = (vdp_Color32*)kk_cptr_raw_unbox_borrowed(color_boxed_ptr, ctx);
  uint8_t a = color->a;
  kk_box_drop(color_boxed_ptr, ctx);
  return a;
}

static void kk_dbsdk_vdp__free_Rect(void *rect_ptr, kk_block_t *b, kk_context_t *ctx) {
  kk_unused(ctx);
  vdp_Rect *rect = (vdp_Rect*)rect_ptr;
  if (rect != NULL) free(rect);
}

kk_box_t kk_dbsdk_vdp__alloc_Rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, kk_context_t *ctx) {
  vdp_Rect *rect = malloc(sizeof(vdp_Rect));
  *rect = (vdp_Rect){.x = x, .y = y, .w = w, .h = h};
  return kk_cptr_raw_box(&kk_dbsdk_vdp__free_Rect, rect, ctx);
}

uint32_t kk_dbsdk_vdp__Rect_x(kk_box_t rect_boxed_ptr, kk_context_t *ctx) {
  vdp_Rect *rect = (vdp_Rect*)kk_cptr_raw_unbox_borrowed(rect_boxed_ptr, ctx);
  uint32_t x = rect->x;
  kk_box_drop(rect_boxed_ptr, ctx);
  return x;
}

uint32_t kk_dbsdk_vdp__Rect_y(kk_box_t rect_boxed_ptr, kk_context_t *ctx) {
  vdp_Rect *rect = (vdp_Rect*)kk_cptr_raw_unbox_borrowed(rect_boxed_ptr, ctx);
  uint32_t y = rect->y;
  kk_box_drop(rect_boxed_ptr, ctx);
  return y;
}

uint32_t kk_dbsdk_vdp__Rect_w(kk_box_t rect_boxed_ptr, kk_context_t *ctx) {
  vdp_Rect *rect = (vdp_Rect*)kk_cptr_raw_unbox_borrowed(rect_boxed_ptr, ctx);
  uint32_t w = rect->w;
  kk_box_drop(rect_boxed_ptr, ctx);
  return w;
}

uint32_t kk_dbsdk_vdp__Rect_h(kk_box_t rect_boxed_ptr, kk_context_t *ctx) {
  vdp_Rect *rect = (vdp_Rect*)kk_cptr_raw_unbox_borrowed(rect_boxed_ptr, ctx);
  uint32_t h = rect->h;
  kk_box_drop(rect_boxed_ptr, ctx);
  return h;
}

kk_unit_t kk_dbsdk_vdp__initialize(kk_box_t initial_state, kk_context_t *ctx) {
  KOKA_CTX = ctx;
  kk_box_dup(initial_state, ctx);
  CURRENT_STATE = initial_state;
  return kk_Unit;
}