#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define PI 3.14159265359f
#define DEG_2_RAD (PI / 180.0f)
#define RAD_2_DEG (180.0f / PI)

#define MAT4_IDENTITY               \
    (Mat4)                          \
    {                               \
        1.0f, 0.0f, 0.0f, 0.0f,     \
            0.0f, 1.0f, 0.0f, 0.0f, \
            0.0f, 0.0f, 1.0f, 0.0f, \
            0.0f, 0.0f, 0.0f, 1.0f  \
    }

#define QUATERNION_IDENTITY \
    (Quaternion) { 0.0f, 0.0f, 0.0f, 1.0f }

/// @brief A two-component vector
typedef struct
{
    float x;
    float y;
} Vec2;

/// @brief A three-component vector
typedef struct
{
    float x;
    float y;
    float z;
} Vec3;

/// @brief A four-component vector
typedef struct
{
    float x;
    float y;
    float z;
    float w;
} Vec4;

/// @brief A quaternion
typedef struct
{
    float x;
    float y;
    float z;
    float w;
} Quaternion;

/// @brief A 4x4 matrix
typedef struct
{
    float m[4][4];
} Mat4;

/// @brief Get the length of a vector
/// @param v 
/// @return The length of the vector
float vec2_length(Vec2 v);

/// @brief Get the length of a vector
/// @param v
/// @return The length of the vector
float vec3_length(Vec3 v);

/// @brief Get the squared length of a vector
/// @param v
/// @return The squared length of the vector
float vec2_lengthSq(Vec2 v);

/// @brief Get the squared length of a vector
/// @param v
/// @return The squared length of the vector
float vec3_lengthSq(Vec3 v);

/// @brief Get the distance between two vectors
/// @param lhs 
/// @param rhs 
/// @return The distance between the given vectors
float vec2_distance(Vec2 lhs, Vec2 rhs);

/// @brief Get the distance between two vectors
/// @param lhs
/// @param rhs
/// @return The distance between the given vectors
float vec3_distance(Vec3 lhs, Vec3 rhs);

/// @brief Get the squared distance between two vectors
/// @param lhs
/// @param rhs
/// @return The squared distance between the given vectors
float vec2_distanceSq(Vec2 lhs, Vec2 rhs);

/// @brief Get the squared distance between two vectors
/// @param lhs
/// @param rhs
/// @return The squared distance between the given vectors
float vec3_distanceSq(Vec3 lhs, Vec3 rhs);

/// @brief Clamp the value between a minimum and maximum
/// @param value 
/// @param min 
/// @param max 
/// @return A value clamped between min and max
float clamp(float value, float min, float max);

/// @brief Linearly interpolate between two values
/// @param lhs 
/// @param rhs 
/// @param t 
/// @return A value between lhs and rhs
float lerp(float lhs, float rhs, float t);

/// @brief Linearly interpolate between two values
/// @param lhs
/// @param rhs
/// @param t
/// @return A value between lhs and rhs
Vec2 vec2_lerp(Vec2 lhs, Vec2 rhs, float t);

/// @brief Linearly interpolate between two values
/// @param lhs
/// @param rhs
/// @param t
/// @return A value between lhs and rhs
Vec3 vec3_lerp(Vec3 lhs, Vec3 rhs, float t);

/// @brief Linearly interpolate between two values
/// @param lhs
/// @param rhs
/// @param t
/// @return A value between lhs and rhs
Vec4 vec4_lerp(Vec4 lhs, Vec4 rhs, float t);

/// @brief Componentwise-mutiply two vectors
/// @param lhs 
/// @param rhs 
/// @return The product of both vectors
Vec2 vec2_mul(Vec2 lhs, Vec2 rhs);

/// @brief Componentwise-mutiply two vectors
/// @param lhs
/// @param rhs
/// @return The product of both vectors
Vec3 vec3_mul(Vec3 lhs, Vec3 rhs);

/// @brief Componentwise-mutiply two vectors
/// @param lhs
/// @param rhs
/// @return The product of both vectors
Vec4 vec4_mul(Vec4 lhs, Vec4 rhs);

/// @brief Add two vectors
/// @param lhs
/// @param rhs
/// @return The sum of both vectors
Vec2 vec2_add(Vec2 lhs, Vec2 rhs);

/// @brief Add two vectors
/// @param lhs
/// @param rhs
/// @return The sum of both vectors
Vec3 vec3_add(Vec3 lhs, Vec3 rhs);

/// @brief Add two vectors
/// @param lhs
/// @param rhs
/// @return The sum of both vectors
Vec4 vec4_add(Vec4 lhs, Vec4 rhs);

/// @brief Subtract two vectors
/// @param lhs
/// @param rhs
/// @return The difference of both vectors
Vec2 vec2_sub(Vec2 lhs, Vec2 rhs);

/// @brief Subtract two vectors
/// @param lhs
/// @param rhs
/// @return The difference of both vectors
Vec3 vec3_sub(Vec3 lhs, Vec3 rhs);

/// @brief Subtract two vectors
/// @param lhs
/// @param rhs
/// @return The difference of both vectors
Vec4 vec4_sub(Vec4 lhs, Vec4 rhs);

/// @brief Divide two vectors
/// @param lhs
/// @param rhs
/// @return The quotient of both vectors
Vec2 vec2_div(Vec2 lhs, Vec2 rhs);

/// @brief Divide two vectors
/// @param lhs
/// @param rhs
/// @return The quotient of both vectors
Vec3 vec3_div(Vec3 lhs, Vec3 rhs);

/// @brief Divide two vectors
/// @param lhs
/// @param rhs
/// @return The quotient of both vectors
Vec4 vec4_div(Vec4 lhs, Vec4 rhs);

/// @brief Compute the dot product of the given vectors
/// @param lhs The vector on the lefthand side
/// @param rhs The vector on the righthand side
/// @return The dot product of the two vectors
float vec2_dot(Vec2 lhs, Vec2 rhs);

/// @brief Compute the dot product of the given vectors
/// @param lhs The vector on the lefthand side
/// @param rhs The vector on the righthand side
/// @return The dot product of the two vectors
float vec3_dot(Vec3 lhs, Vec3 rhs);

/// @brief Compute the dot product of the given vectors
/// @param lhs The vector on the lefthand side
/// @param rhs The vector on the righthand side
/// @return The dot product of the two vectors
float vec4_dot(Vec4 lhs, Vec4 rhs);

/// @brief Compute the cross product of the given vectors
/// @param lhs The vector on the lefthand side
/// @param rhs The vector on the righthand side
/// @return The cross product of the two vectors
Vec3 vec3_cross(Vec3 lhs, Vec3 rhs);

/// @brief Normalize the given vector
/// @param v The vector to normalize
void vec2_normalize(Vec2 *v);

/// @brief Normalize the given vector
/// @param v The vector to normalize
void vec3_normalize(Vec3 *v);

/// @brief Normalize the given vector
/// @param v The vector to normalize
void vec4_normalize(Vec4 *v);

/// @brief Normalize the given quaternion
/// @param q The quaternion to normalize
void quat_normalize(Quaternion *q);

/// @brief Invert the given quaternion
/// @param q Pointer to the quaternion to invert
void quat_invert(Quaternion *q);

/// @brief Rotate a vector by a quaternion
/// @param q The quaternion representing a rotation
/// @param v The vector to rotate
/// @return A rotated vector
Vec3 vec3_transformQuat(Quaternion q, Vec3 v);

/// @brief Multiply two quaternions together
/// @param lhs Quaternion on the lefthand side
/// @param rhs Quaternion on the righthand side
/// @return The multiplied result
Quaternion quat_mul(Quaternion lhs, Quaternion rhs);

/// @brief Construct a quaternion from rotation around each axis
/// @param eulerAngles Rotation around each axis in radians
/// @return An equivalent quaternion
Quaternion quat_fromEuler(Vec3 eulerAngles);

/// @brief Transform a single vector with a matrix without the aid of the SIMD matrix unit
/// @param mat The transform matrix
/// @param vec The vector to transform
/// @return The transformed vector
Vec4 vec4_transform(Mat4 mat, Vec4 vec);

/// @brief Construct a matrix from the given translation
/// @param translation The translation
/// @return A translation matrix
Mat4 mat4_translate(Vec3 translation);

/// @brief Construct a matrix from the given scale
/// @param scale The scale
/// @return A scale matrix
Mat4 mat4_scale(Vec3 scale);

/// @brief Construct a matrix from the given rotation
/// @param rotation The rotation
/// @return A rotation matrix
Mat4 mat4_rotation(Quaternion rotation);

/// @brief Construct an orthographic projection matrix
/// @param left The left side of the frustum
/// @param right The right side of the frustum
/// @param top The top side of the frustum
/// @param bottom The bottom side of the frustum
/// @param near The near clip distance
/// @param far The far clip distance
/// @return An orthographic projection matrix
Mat4 mat4_projectionOrtho(float left, float right, float top, float bottom, float near, float far);

/// @brief Construct an orthographic projection matrix
/// @param aspectRatio The aspect ratio of the frustum (width/height)
/// @param scale The height of the frustum
/// @param near The near clip distance
/// @param far The far clip distance
/// @return An orthographic projection matrix centered at origin
Mat4 mat4_projectionOrthoAspect(float aspectRatio, float scale, float near, float far);

/// @brief Construct a perspective projection matrix
/// @param aspectRatio The aspect ratio of the frustum (width/height)
/// @param fieldOfView The vertical field of view in radians
/// @param near The near clip distance
/// @param far The far clip distance
/// @return A perspective projection matrix centered at origin
Mat4 mat4_projectionPerspective(float aspectRatio, float fieldOfView, float near, float far);

/// @brief Multiply two matrices together manually without the aid of the SIMD matrix unit
/// @param lhs Matrix on the lefthand side
/// @param rhs Matrix on the righthand side
/// @return The multiplied matrix result
Mat4 mat4_mul(Mat4 lhs, Mat4 rhs);

/// @brief Load identity matrix into the SIMD matrix register
void mat4_loadIdentitySIMD();

/// @brief Load a matrix into the SIMD matrix register
/// @param mat The matrix to load
extern void mat4_loadSIMD(const Mat4 *mat);

/// @brief Store the value in the SIMD matrix register to the given matrix
/// @param mat The matrix to store the value into
extern void mat4_storeSIMD(Mat4 *mat);

/// @brief Multiply internal SIMD matrix register with the given matrix
/// @param mat The matrix to multiply into the SIMD matrix register
extern void mat4_mulSIMD(const Mat4 *mat);

/// @brief Transform a list of input Vec4s using the SIMD matrix unit
/// @param invec Pointer to list of input vectors to transform
/// @param outvec Pointer to list of output vectors to write
/// @param count Number of vectors to transform
/// @param stride Number of bytes between each vector (0 implies tightly packed array of Vec4)
extern void mat4_transformSIMD(const Vec4 *invec, Vec4 *outvec, uint32_t count, uint32_t stride);

#ifdef __cplusplus
}
#endif