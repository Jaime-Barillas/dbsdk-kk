#pragma once

#include <stdint.h>
#include "db_math.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define VDP_TEXFMT_RGB565 0
#define VDP_TEXFMT_RGBA4444 1
#define VDP_TEXFMT_RGBA8888 2
#define VDP_TEXFMT_DXT1 3
#define VDP_TEXFMT_DXT3 4
#define VDP_TEXFMT_YUV420 5

#define VDP_FILTER_NEAREST 0x2600
#define VDP_FILTER_LINEAR 0x2601

#define VDP_WRAP_REPEAT 0x2901
#define VDP_WRAP_CLAMP 0x812F
#define VDP_WRAP_MIRROR 0x8370

#define VDP_COMPARE_NEVER 0x0200
#define VDP_COMPARE_LESS 0x0201
#define VDP_COMPARE_EQUAL 0x0202
#define VDP_COMPARE_LEQUAL 0x0203
#define VDP_COMPARE_GREATER 0x0204
#define VDP_COMPARE_NOTEQUAL 0x0205
#define VDP_COMPARE_GEQUAL 0x0206
#define VDP_COMPARE_ALWAYS 0x0207

#define VDP_FUNC_ADD 0x8006
#define VDP_FUNC_SUBTRACT 0x800A
#define VDP_FUNC_REVERSE_SUBTRACT 0x800B

#define VDP_BLEND_ZERO 0
#define VDP_BLEND_ONE 1
#define VDP_BLEND_SRC_COLOR 0x0300
#define VDP_BLEND_ONE_MINUS_SRC_COLOR 0x0301
#define VDP_BLEND_SRC_ALPHA 0x0302
#define VDP_BLEND_ONE_MINUS_SRC_ALPHA 0x0303
#define VDP_BLEND_DST_ALPHA 0x0304
#define VDP_BLEND_ONE_MINUS_DST_ALPHA 0x0305
#define VDP_BLEND_DST_COLOR 0x0306
#define VDP_BLEND_ONE_MINUS_DST_COLOR 0x0307

#define VDP_WINDING_CW 0x0900
#define VDP_WINDING_CCW 0x0901

#define VDP_TOPOLOGY_LINES 0x0000
#define VDP_TOPOLOGY_LINE_STRIP 0x0001
#define VDP_TOPOLOGY_TRIANGLES 0x0002
#define VDP_TOPOLOGY_TRIANGLE_STRIP 0x0003

/// @brief An axis-aligned rectangle
typedef struct
{
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
} vdp_Rect;

/// @brief A 32-bit color
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} vdp_Color32;

/// @brief A vertex which can be passed to vdp_drawGeometry
typedef struct
{
    /// @brief The position of the vertex
    Vec4 position;

    /// @brief The vertex color (multiplied with currently bound texture)
    Vec4 color;

    /// @brief The vertex offset color (added to color * texture)
    Vec4 ocolor;

    /// @brief The texture coordinate used to sample the currently bound texture
    Vec4 texcoord;
} vdp_Vertex;

/// @brief A vertex which can be passed to vdp_drawGeometryPacked
typedef struct
{
    /// @brief The position of the vertex
    Vec4 position;

    /// @brief The texture coordinate used to sample the currently bound texture
    Vec2 texcoord;

    /// @brief The vertex color (multiplied with currently bound texture)
    vdp_Color32 color;

    /// @brief The vertex offset color (added to color * texture)
    vdp_Color32 ocolor;
} vdp_PackedVertex;

/// @brief Callback type for vsync
typedef void (*vsync_handler_t)();

/// @brief Clear framebuffer to the given color value
/// @param color
extern void vdp_clearColor(const vdp_Color32 *color);

/// @brief Clear depth buffer to the given depth value
/// @param depth
extern void vdp_clearDepth(float depth);

/// @brief Set whether depth writes are enabled or disabled
/// @param enable
extern void vdp_depthWrite(uint8_t enable);

/// @brief Set the depth test function
/// @param comparison
extern void vdp_depthFunc(uint32_t comparison);

/// @brief Set the blend equation mode
/// @param mode
extern void vdp_blendEquation(uint32_t mode);

/// @brief Set the blend equation factors
/// @param srcFactor
/// @param dstFactor
extern void vdp_blendFunc(uint32_t srcFactor, uint32_t dstFactor);

/// @brief Set the winding order of vertices for backface culling
/// @param windingOrder
extern void vdp_setWinding(uint32_t windingOrder);

/// @brief Set whether backface culling is enabled or disabled
/// @param enabled
extern void vdp_setCulling(uint8_t enabled);

/// @brief Draw geometry to the screen
/// @param topology
/// @param first
/// @param count
/// @param vertexData
extern void vdp_drawGeometry(uint32_t topology, uint32_t first, uint32_t count, const vdp_Vertex *vertexData);

/// @brief Draw geometry to the screen using the packed vertex format
/// @param topology
/// @param first
/// @param count
/// @param vertexData
extern void vdp_drawGeometryPacked(uint32_t topology, uint32_t first, uint32_t count, const vdp_PackedVertex *vertexData);

/// @brief Allocate a texture
/// @param mipmap
/// @param format
/// @param width
/// @param height
/// @return A handle to the allocated texture (or -1 if allocation failed)
extern uint32_t vdp_allocTexture(uint8_t mipmap, uint32_t format, uint32_t width, uint32_t height);

/// @brief Release previously allocated texture
/// @param textureHandle
extern void vdp_releaseTexture(uint32_t textureHandle);

/// @brief Upload data to an allocated texture
/// @param textureHandle
/// @param level
/// @param data
/// @param dataLen
extern void vdp_setTextureData(uint32_t textureHandle, uint32_t level, const void *data, uint32_t dataLen);

/// @brief Upload individual color planes to an allocated YUV texture
/// @param textureHandle
/// @param yData
/// @param yDataLen
/// @param uData
/// @param uDataLen
/// @param vData
/// @param vDataLen
extern void vdp_setTextureDataYUV(uint32_t textureHandle, const void *yData, uint32_t yDataLen, const void *uData, uint32_t uDataLen, const void *vData, uint32_t vDataLen);

/// @brief Upload data to a region of an allocated texture
/// @param textureHandle
/// @param level
/// @param dstRect
/// @param data
/// @param dataLen
extern void vdp_setTextureDataRegion(uint32_t textureHandle, uint32_t level, vdp_Rect *dstRect, const void *data, uint32_t dataLen);

/// @brief Copy a portion of the framebuffer into a texture
/// @param srcRect Source rectangle of the framebuffer to copy
/// @param dstRect Destination rectangle of the texture to copy into
/// @param textureHandle The destination texture to copy into
extern void vdp_copyFbToTexture(vdp_Rect *srcRect, vdp_Rect *dstRect, uint32_t textureHandle);

/// @brief Report total texture memory usage in bytes
/// @return
extern uint32_t vdp_getUsage();

/// @brief Set texture sampling params
/// @param filter
/// @param wrapU
/// @param wrapV
extern void vdp_setSampleParams(uint32_t filter, uint32_t wrapU, uint32_t wrapV);

/// @brief Set texture to use for rendering
/// @param textureHandle
extern void vdp_bindTexture(uint32_t textureHandle);

/// @brief Set the current viewport rect
/// @param x
/// @param y
/// @param width
/// @param height
extern void vdp_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

/// @brief Submit a depth query of a portion of the framebuffer, comparing a region of it against a specified value
/// @param refVal The reference value to compare against
/// @param comparison The comparison to use
/// @param x The x coordinate of the region's top left corner
/// @param y The y coordinate of the region's top left corner
/// @param w The width of the region
/// @param h The height of the region
extern void vdp_submitDepthQuery(float refVal, uint32_t comparison, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

/// @brief Get the results of the previously submitted depth query
/// @return The number of pixels which passed the depth comparison within the region specified
extern uint32_t vdp_getDepthQueryResult();

/// @brief Set a callback handler for vsync
/// @param handler
extern void vdp_setVsyncHandler(const vsync_handler_t handler);

#ifdef __cplusplus
}
#endif
