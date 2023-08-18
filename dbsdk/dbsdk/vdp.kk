module dbsdk/vdp

pub type gfx :: X // Marks functions which render to the screen.

extern import
  c header-end-file "db_vdp-inline.h"

// FIXME: Is it correct to label this C function as write<h>? Should it also be
// read<h>?
pub inline extern initialize(state: a): <read<h>,write<h>> ()
  c "kk_dbsdk_vdp__initialize"

// FIXME: Is it correct to label this C function as write<h>? Should it also be
// read<h>?
// NOTE: Type `a` here is (MUST be) the same `a` as in `initialize` above!
pub inline extern set-vsync-handler(func: (a) -> e a): write<h> ()
  c "kk_dbsdk_vdp__vdp_setVsyncHandler"

//======  ======//

pub ref struct color32
  r: int
  g: int
  b: int
  a: int

pub inline extern clear-color(color: color32): gfx ()
  c "kk_dbsdk_vdp__vdp_clearColor"

pub ref struct vec4
  x: float64 = 0.0
  y: float64 = 0.0
  z: float64 = 0.0
  w: float64 = 0.0
pub ref struct vertex
  position: vec4
  color: vec4
  ocolor: vec4 = Vec4()
  texcoord: vec4 = Vec4()
pub inline extern draw-geometry(vertex-data: vector<vertex>): gfx ()
  c "kk_dbsdk_vdp__vdp_drawGeometry"