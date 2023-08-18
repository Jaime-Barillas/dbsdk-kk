//#include <db_vdp.h>
#include <stdint.h>
extern void vdp_setVsyncHandler(void (*)());

// Work-around so the Koka provided tick function can be sent to
// `vdp_setVsyncHandler` without args and still know which function to call
// with what ctx. `vdp_setVsyncHandler` requires a function that takes no
// arguments and returns void. The workaround
static kk_context_t* KOKA_CTX;
static kk_function_t TICK_FUNCTION;
static kk_box_t CURRENT_STATE;

static inline kk_unit_t kk_dbsdk_vdp__initialize(kk_box_t state, kk_context_t* ctx) {
  KOKA_CTX = ctx;
  kk_box_dup(state, ctx);
  CURRENT_STATE = state;
  return kk_Unit;
}

static void dbsdk_vdp__internal__tick_func(void) {
  CURRENT_STATE = kk_function_call(kk_box_t, (kk_function_t, kk_box_t, kk_context_t*), TICK_FUNCTION, (TICK_FUNCTION, CURRENT_STATE, KOKA_CTX), KOKA_CTX);
}

static inline kk_unit_t kk_dbsdk_vdp__vdp_setVsyncHandler(kk_function_t tick, kk_context_t* ctx) {
  kk_function_dup(tick, ctx);
  TICK_FUNCTION = tick;
  vdp_setVsyncHandler(dbsdk_vdp__internal__tick_func);
  return kk_Unit;
}

// TODO: Continue from here:

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} vdp_Color32;
extern void vdp_clearColor(const vdp_Color32*);
static kk_unit_t kk_dbsdk_vdp__vdp_clearColor(kk_dbsdk_vdp__color32 color, kk_context_t* ctx) {
  // Alternatively, use the generated accessor functions.
  // `kk_dbsdk_vdp__as_Color32` is used to avoid having to call
  // `kk_integer_drop` on the fields. NOTE: I don't know if this usage is
  // correct considering the fields are passed to `kk_integer_clamp_byte`...
  struct kk_dbsdk_vdp_Color32 *color32 = kk_dbsdk_vdp__as_Color32(color, ctx);
  uint8_t r = kk_integer_clamp_byte(color32->r, ctx);
  uint8_t g = kk_integer_clamp_byte(color32->g, ctx);
  uint8_t b = kk_integer_clamp_byte(color32->b, ctx);
  uint8_t a = kk_integer_clamp_byte(color32->a, ctx);
  vdp_Color32 clear_color = {.r = r, .g = g, .b = b, .a = a};
  // If using accessor functions, Color32 fields can be dropped here.
  vdp_clearColor(&clear_color);
  return kk_Unit;
}
typedef struct {
  float x;
  float y;
  float z;
  float w;
} Vec4;
typedef struct {
  Vec4 position;
  Vec4 color;
  Vec4 ocolor;
  Vec4 texcoord;
} vdp_Vertex;
extern void vdp_drawGeometry(uint32_t topology, uint32_t first, uint32_t count, vdp_Vertex* vertexData);
//extern void vdp_blendEquation(uint32_t);
//extern void vdp_blendFunc(uint32_t, uint32_t);
static kk_unit_t kk_dbsdk_vdp__vdp_drawGeometry(kk_vector_t xs, kk_context_t* ctx) {
  //vdp_blendEquation(0x8006); // ADD
  //vdp_blendFunc(1, 0); // Blend_one & blend_zero
  kk_ssize_t length = 0;
  kk_box_t* buf = kk_vector_buf_borrow(xs, &length, ctx);
  
  vdp_Vertex* verts = malloc(length * sizeof(vdp_Vertex));
  for(kk_ssize_t i = 0; i < length; i++) {
    kk_dbsdk_vdp__vertex vert = kk_dbsdk_vdp__vertex_unbox(buf[i], KK_BORROWED /*Seems to be unused in fn*/, ctx);
    kk_dbsdk_vdp__vec4 pos = kk_dbsdk_vdp_position(vert, ctx);
    kk_dbsdk_vdp__vec4 color = kk_dbsdk_vdp_color(vert, ctx);
    verts[i] = (vdp_Vertex){
      .position = {.x = (float)kk_dbsdk_vdp_x(pos, ctx),
                   .y = (float)kk_dbsdk_vdp_y(pos, ctx),
                   .z = (float)kk_dbsdk_vdp_z(pos, ctx),
                   .w = (float)kk_dbsdk_vdp_w(pos, ctx)},
      .color = {.x = (float)kk_dbsdk_vdp_x(color, ctx),
                .y = (float)kk_dbsdk_vdp_y(color, ctx),
                .z = (float)kk_dbsdk_vdp_z(color, ctx),
                .w = (float)kk_dbsdk_vdp_w(color, ctx)},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    };
  }
  vdp_drawGeometry(2 /*VDP_TOPOLOGY_TRIANGLES*/, 0, 3, verts);
  free(verts);
  return kk_Unit;
}