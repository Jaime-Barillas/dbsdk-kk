module dbsdk/vdp

import std/num/float64
import std/num/int32

extern import
  c header-file "c/include/db_vdp.h"

extern import
  c file "vdp-inline"

abstract struct color32(boxed_ptr: any)

// NOTE: The void type is not made public. Will declaring it myself work
// correctly? All vdp_* functions that return void are wrapped in a C
// function that returns kk_unit_t for now.

inline extern dbsdk-vdp-clearColor(c: any): ()
  c "kk_dbsdk_vdp__vdp_clearColor"

inline extern dbsdk-vdp-clearDepth(d: float32): ()
  c "dbsdk_vdp__vdp_clearDepth"

inline extern dbsdk-vdp-depthWrite(e: int8): ()
  c "dbsdk_vdp__vdp_depthWrite"

inline extern dbsdk-vdp-depthFunc(c: int32): ()
  c "dbsdk_vdp__vdp_depthFunc"

inline extern dbsdk-vdp-blendEquation(m: int32): ()
  c "dbsdk_vdp__vdp_blendEquation"

inline extern dbsdk-vdp-blendFunc(s: int32, d: int32): ()
  c "dbsdk_vdp__vdp_blendFunc"

inline extern dbsdk-vdp-setWinding(w: int32): ()
  c "dbsdk_vdp__vdp_setWinding"

inline extern dbsdk-vdp-setCulling(e: int8): ()
  c "dbsdk_vdp__vdp_setCulling"

inline extern dbsdk-vdp-setVsyncHandler(t: (s) -> e s): ()
  c "kk_dbsdk_vdp__vdp_setVsyncHandler"

// NOTE: The following int8's for Color32 functions are actually uint8_t's.
inline extern dbsdk-vdp-alloc-Color32(r: int8, g: int8, b: int8, a: int8): any
  c "kk_dbsdk_vdp__alloc_Color32"

inline extern dbsdk-vdp-Color32-r(c: any): int8
  c "kk_dbsdk_vdp__Color32_r"

inline extern dbsdk-vdp-Color32-g(c: any): int8
  c "kk_dbsdk_vdp__Color32_g"

inline extern dbsdk-vdp-Color32-b(c: any): int8
  c "kk_dbsdk_vdp__Color32_b"

inline extern dbsdk-vdp-Color32-a(c: any): int8
  c "kk_dbsdk_vdp__Color32_a"

inline extern dbsdk-vdp-initialize(state: s): ()
  c "kk_dbsdk_vdp__initialize"



pub type depthFunc
  Never
  Less
  Equal
  Lequal
  Greater
  NotEqual
  Gequal
  Always

pub type blendMode
  Add
  Subtract
  ReverseSubtract

pub type blendFactor
  Zero
  One
  SrcColor
  OneMinusSrcColor
  SrcAlpha
  OneMinusSrcAlpha
  DstAlpha
  OneMinusDstAlpha
  DstColor
  OneMinusDstColor

pub type windingOrder
  CW
  CCW

fun blendFactor-to-int(b: blendFactor): int
  match b
    Zero -> 0
    One -> 1
    SrcColor -> 0x0300
    OneMinusSrcColor -> 0x0301
    SrcAlpha -> 0x0302
    OneMinusSrcAlpha -> 0x0303
    DstAlpha -> 0x0304
    OneMinusDstAlpha -> 0x0305
    DstColor -> 0x0306
    OneMinusDstColor -> 0x0307

pub fun clear-color(color: color32): ()
  dbsdk-vdp-clearColor(color.boxed_ptr)

pub fun clear-depth(depth: float64): ()
  dbsdk-vdp-clearDepth(depth.float32())

pub fun depth-write(enable: bool): ()
  val c_bool = match enable
    True -> 1
    False -> 0
  dbsdk-vdp-depthWrite(c_bool.int8())

pub fun depth-func(comparison: depthFunc): ()
  val c_depth_func = match comparison
    Never -> 0x0200
    Less -> 0x0201
    Equal -> 0x0202
    Lequal -> 0x0203
    Greater -> 0x0204
    NotEqual -> 0x0205
    Gequal -> 0x0206
    Always -> 0x0207
  dbsdk-vdp-depthFunc(c_depth_func.uint32())

pub fun blend-equation(mode: blendMode): ()
  val c_blend_equation = match mode
    Add -> 0x8006
    Subtract -> 0x800a
    ReverseSubtract -> 0x800b
  dbsdk-vdp-blendEquation(c_blend_equation.uint32())

pub fun blend-func(src-factor: blendFactor, dst-factor: blendFactor): ()
  val c_src_factor = blendFactor-to-int(src-factor)
  val c_dst_factor = blendFactor-to-int(dst-factor)
  dbsdk-vdp-blendFunc(c_src_factor.uint32(), c_dst_factor.uint32())

pub fun set-winding(winding-order: windingOrder): ()
  val c_winding_order = match winding-order
    CW -> 0x0900
    CCW -> 0x0901
  dbsdk-vdp-setWinding(c_winding_order.uint32())

pub fun set-culling(enabled: bool)
  val c_bool = match enabled
    True -> 1
    False -> 0
  dbsdk-vdp-setCulling(c_bool.uint8())

//pub fun draw-geometry()

//pub fun draw-geometry-packed()

pub fun set-vsync-handler<gamestate>(tick: (gamestate) -> e gamestate): ()
  dbsdk-vdp-setVsyncHandler(tick)

pub fun alloc-color32(r: int, g: int, b: int, a: int): color32
  Color32(dbsdk-vdp-alloc-Color32(r.uint8(), g.uint8(), b.uint8(), a.uint8()))

pub fun r(color: color32): int
  dbsdk-vdp-Color32-r(color.boxed_ptr).uint()

pub fun g(color: color32): int
  dbsdk-vdp-Color32-g(color.boxed_ptr).uint()

pub fun b(color: color32): int
  dbsdk-vdp-Color32-b(color.boxed_ptr).uint()

pub fun a(color: color32): int
  dbsdk-vdp-Color32-a(color.boxed_ptr).uint()

pub fun initialize<gamestate>(initial-state: gamestate): ()
  dbsdk-vdp-initialize(initial-state)