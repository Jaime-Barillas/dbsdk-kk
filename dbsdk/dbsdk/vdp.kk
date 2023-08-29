module dbsdk/vdp

import std/num/float64
import std/num/int32

extern import
  c header-file "c/include/db_vdp.h"

extern import
  c file "vdp-inline"

abstract struct color32(boxed_ptr: any)

abstract struct rect(boxed_ptr: any)

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

// draw-geometry
// draw-geometry-packed

inline extern dbsdk-vdp-allocTexture(m: int8, f: int32, w: int32, h: int32): int32
  c "vdp_allocTexture"

inline extern dbsdk-vdp-releaseTexture(h: int32): ()
  c "dbsdk_vdp__vdp_releaseTexture"

inline extern dbsdk-vdp-setTextureData(h: int32, l: int32, d: intptr_t, l: int32): ()
  c "dbsdk_vdp__vdp_setTextureData"

inline extern dbsdk-vdp-setTextureDataYUV(h: int32, y: intptr_t, yl: int32, u: intptr_t, ul: int32, v: intptr_t, vl: int32): ()
  c "dbsdk_vdp__vdp_setTextureDataYUV"

inline extern dbsdk-vdp-setTextureDataRegion(h: int32, l: int32, r: any, d: intptr_t, dl: int32): ()
  c "kk_dbsdk_vdp__vdp_setTextureDataRegion"

inline extern dbsdk-vdp-copyFbToTexture(s: any, d: any, h: int32): ()
  c "kk_dbsdk_vdp__vdp_copyFbToTexture"

inline extern dbsdk-vdp-getUsage(): int32
  c "vdp_getUsage"

inline extern dbsdk-vdp-setSampleParams(f: int32, u: int32, v: int32): ()
  c "dbsdk_vdp__vdp_setSampleParams"

inline extern dbsdk-vdp-bindTexture(h: int32): ()
  c "dbsdk_vdp__vdp_bindTexture"

inline extern dbsdk-vdp-viewport(x: int32, y: int32, w: int32, h: int32): ()
  c "dbsdk_vdp__vdp_viewport"

inline extern dbsdk-vdp-submitDepthQuery(r: float32, c: int32, x: int32, y: int32, w: int32, h: int32): ()
  c "dbsdk_vdp__vdp_submitDepthQuery"

inline extern dbsdk-vdp-getDepthQueryResult(): int32
  c "vdp_getDepthQueryResult"

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

// NOTE: The following int32's for Rect functions are actually uint32_t's.
inline extern dbsdk-vdp-alloc-Rect(x: int32, y: int32, w: int32, x: int32): any
  c "kk_dbsdk_vdp__alloc_Rect"

inline extern dbsdk-vdp-Rect-x(r: any): int32
  c "kk_dbsdk_vdp__Rect_x"

inline extern dbsdk-vdp-Rect-y(r: any): int32
  c "kk_dbsdk_vdp__Rect_y"

inline extern dbsdk-vdp-Rect-w(r: any): int32
  c "kk_dbsdk_vdp__Rect_w"

inline extern dbsdk-vdp-Rect-h(r: any): int32
  c "kk_dbsdk_vdp__Rect_h"

inline extern dbsdk-vdp-initialize(state: s): ()
  c "kk_dbsdk_vdp__initialize"



pub type depthComparison
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

pub type textureFormat
  RGB565
  RGBA4444
  RGBA8888
  DXT1
  DXT3
  YUV420

pub type filterMode
  Nearest
  Linear

pub type wrapMode
  Repeat
  Clamp

fun depthComparison-to-int(c: depthComparison): int
  match c
    Never -> 0x0200
    Less -> 0x0201
    Equal -> 0x0202
    Lequal -> 0x0203
    Greater -> 0x0204
    NotEqual -> 0x0205
    Gequal -> 0x0206
    Always -> 0x0207

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

fun wrapMode-to-int(w: wrapMode): int
  match w
    Repeat -> 0x2901
    Clamp -> 0x812f

pub fun clear-color(color: color32): ()
  dbsdk-vdp-clearColor(color.boxed_ptr)

pub fun clear-depth(depth: float64): ()
  dbsdk-vdp-clearDepth(depth.float32())

pub fun depth-write(enable: bool): ()
  val c_bool = match enable
    True -> 1
    False -> 0
  dbsdk-vdp-depthWrite(c_bool.int8())

pub fun depth-func(comparison: depthComparison): ()
  val c_depth_func = depthComparison-to-int(comparison)
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
pub fun alloc-texture(mipmap: bool, format: textureFormat, width: int, height: int): int32
  val c_mipmap = match mipmap
    True -> 1
    False -> 0
  val c_format = match format
    RGB565 -> 0
    RGBA4444 -> 1
    RGBA8888 -> 2
    DXT1 -> 3
    DXT3 -> 4
    YUV420 -> 5
  dbsdk-vdp-allocTexture(c_mipmap.uint8(), c_format.uint32(), width.uint32(), height.uint32())

pub fun release-texture(texture-handle: int32): ()
  dbsdk-vdp-releaseTexture(texture-handle)

pub fun set-texture-data(texture-handle: int32, level: int, data: intptr_t, length: int): ()
  dbsdk-vdp-setTextureData(texture-handle, level.uint32(), data, length.uint32())

pub fun set-texture-data-yuv(texture-handle: int32, y-data: intptr_t, y-length: int, u-data: intptr_t, u-length: int, v-data: intptr_t, v-length: int): ()
  dbsdk-vdp-setTextureDataYUV(texture-handle, y-data, y-length.uint32(), u-data, u-length.uint32(), v-data, v-length.uint32())

pub fun set-texture-data-region(texture-handle: int32, level: int, dst-rect: rect, data: intptr_t, length: int): ()
  dbsdk-vdp-setTextureDataRegion(texture-handle, level.uint32(), dst-rect.boxed_ptr, data, length.uint32())

pub fun copy-fb-to-texture(src-rect: rect, dst-rect: rect, texture-handle: int32): ()
  dbsdk-vdp-copyFbToTexture(src-rect.boxed_ptr, dst-rect.boxed_ptr, texture-handle)

pub fun get-usage(): int
  dbsdk-vdp-getUsage().uint()

pub fun set-sample-params(filter: filterMode, wrap-u: wrapMode, wrap-v: wrapMode): ()
  val c_filter_mode = match filter
    Nearest -> 0x2600
    Linear -> 0x2601
  val c_wrap_u = wrapMode-to-int(wrap-u)
  val c_wrap_v = wrapMode-to-int(wrap-v)
  dbsdk-vdp-setSampleParams(c_filter_mode.uint32(), c_wrap_u.uint32(), c_wrap_v.uint32())

pub fun bind-texture(texture-handle: int32)
  dbsdk-vdp-bindTexture(texture-handle)

pub fun viewport(x: int, y: int, width: int, height: int): ()
  dbsdk-vdp-viewport(x.uint32(), y.uint32(), width.uint32(), height.uint32())

pub fun submit-depth-query(ref-val: float64, comparison: depthComparison, x: int, y: int, width: int, height: int)
  val c_comparison = depthComparison-to-int(comparison)
  dbsdk-vdp-submitDepthQuery(ref-val.float32(), c_comparison.uint32(), x.uint32(), y.uint32(), width.uint32(), height.uint32())

pub fun get-depth-query-result(): int
  dbsdk-vdp-getDepthQueryResult().uint()

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

pub fun alloc-rect(x: int, y: int, w: int, h: int): rect
  Rect(dbsdk-vdp-alloc-Rect(x.uint32(), y.uint32(), w.uint32(), h.uint32()))

pub fun x(rect: rect): int
  dbsdk-vdp-Rect-x(rect.boxed_ptr).uint()

pub fun y(rect: rect): int
  dbsdk-vdp-Rect-y(rect.boxed_ptr).uint()

pub fun w(rect: rect): int
  dbsdk-vdp-Rect-w(rect.boxed_ptr).uint()

pub fun h(rect: rect): int
  dbsdk-vdp-Rect-h(rect.boxed_ptr).uint()

pub fun initialize<gamestate>(initial-state: gamestate): ()
  dbsdk-vdp-initialize(initial-state)