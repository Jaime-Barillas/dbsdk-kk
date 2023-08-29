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

static void kk_dbsdk_vdp__free_Color32(void *color_ptr, kk_block_t *b, kk_context_t *ctx) {
  kk_unused(ctx);
  vdp_Color32 *color = (vdp_Color32*)color_ptr;
  if (color != NULL) free(color);
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

kk_unit_t kk_dbsdk_vdp__initialize(kk_box_t initial_state, kk_context_t *ctx) {
  KOKA_CTX = ctx;
  kk_box_dup(initial_state, ctx);
  CURRENT_STATE = initial_state;
  return kk_Unit;
}