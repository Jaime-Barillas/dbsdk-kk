static void kk_dbsdk_gamepad__free_State(void *gpad_ptr, kk_block_t *b, kk_context_t *ctx) {
  kk_unused(ctx);
  gamepad_State *gpad = (gamepad_State*)gpad_ptr;
  if (gpad != NULL) free(gpad);
}

kk_box_t kk_dbsdk_gamepad__alloc_State(kk_context_t *ctx) {
  gamepad_State *gpad = malloc(sizeof(gamepad_State));
  return kk_cptr_raw_box(&kk_dbsdk_gamepad__free_State, gpad, ctx);
}

kk_unit_t kk_dbsdk_gamepad__gamepad_readState(uint32_t port, kk_box_t gpad_boxed_ptr, kk_context_t *ctx) {
  gamepad_State *gpad = (gamepad_State*)kk_cptr_raw_unbox_borrowed(gpad_boxed_ptr, ctx);
  gamepad_readState(port, gpad);
  kk_box_drop(gpad_boxed_ptr, ctx);
  return kk_Unit;
}

uint16_t kk_dbsdk_gamepad__State_btnMask(kk_box_t gpad_boxed_ptr, kk_context_t *ctx) {
  gamepad_State *gpad = (gamepad_State*)kk_cptr_raw_unbox_borrowed(gpad_boxed_ptr, ctx);
  uint16_t btnMask = gpad->btnMask;
  kk_box_drop(gpad_boxed_ptr, ctx);
  return btnMask;
}

int16_t kk_dbsdk_gamepad__State_lStickX(kk_box_t gpad_boxed_ptr, kk_context_t *ctx) {
  gamepad_State *gpad = (gamepad_State*)kk_cptr_raw_unbox_borrowed(gpad_boxed_ptr, ctx);
  int16_t lStickX = gpad->lStickX;
  kk_box_drop(gpad_boxed_ptr, ctx);
  return lStickX;
}

int16_t kk_dbsdk_gamepad__State_lStickY(kk_box_t gpad_boxed_ptr, kk_context_t *ctx) {
  gamepad_State *gpad = (gamepad_State*)kk_cptr_raw_unbox_borrowed(gpad_boxed_ptr, ctx);
  int16_t lStickY = gpad->lStickY;
  kk_box_drop(gpad_boxed_ptr, ctx);
  return lStickY;
}

int16_t kk_dbsdk_gamepad__State_rStickX(kk_box_t gpad_boxed_ptr, kk_context_t *ctx) {
  gamepad_State *gpad = (gamepad_State*)kk_cptr_raw_unbox_borrowed(gpad_boxed_ptr, ctx);
  int16_t rStickX = gpad->rStickX;
  kk_box_drop(gpad_boxed_ptr, ctx);
  return rStickX;
}

int16_t kk_dbsdk_gamepad__State_rStickY(kk_box_t gpad_boxed_ptr, kk_context_t *ctx) {
  gamepad_State *gpad = (gamepad_State*)kk_cptr_raw_unbox_borrowed(gpad_boxed_ptr, ctx);
  int16_t rStickY = gpad->rStickY;
  kk_box_drop(gpad_boxed_ptr, ctx);
  return rStickY;
}