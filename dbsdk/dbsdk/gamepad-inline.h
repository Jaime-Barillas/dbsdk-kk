kk_box_t kk_dbsdk_gamepad__alloc_State(kk_context_t*);

kk_unit_t kk_dbsdk_gamepad__gamepad_readState(uint32_t, kk_box_t, kk_context_t*);

static inline kk_unit_t dbsdk_gamepad__gamepad_setRumble(uint32_t port, uint8_t enabled) {
  gamepad_setRumble(port, enabled);
  return kk_Unit;
}

uint16_t kk_dbsdk_gamepad__State_btnMask(kk_box_t, kk_context_t*);
int16_t kk_dbsdk_gamepad__State_lStickX(kk_box_t, kk_context_t*);
int16_t kk_dbsdk_gamepad__State_lStickY(kk_box_t, kk_context_t*);
int16_t kk_dbsdk_gamepad__State_rStickX(kk_box_t, kk_context_t*);
int16_t kk_dbsdk_gamepad__State_rStickY(kk_box_t, kk_context_t*);