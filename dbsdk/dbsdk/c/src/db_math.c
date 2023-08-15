#include <math.h>

#include "db_math.h"
#include "db_log.h"

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

float lerp(float lhs, float rhs, float t)
{
    if (t < 0.0f)
    {
        return lhs;
    }
    if (t > 1.0f)
    {
        return rhs;
    }
    return lhs + ((rhs - lhs) * t);
}

float vec2_length(Vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

float vec3_length(Vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec2_lengthSq(Vec2 v)
{
    return (v.x * v.x + v.y * v.y);
}

float vec3_lengthSq(Vec3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec2_distance(Vec2 lhs, Vec2 rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return vec2_length(lhs);
}

float vec3_distance(Vec3 lhs, Vec3 rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return vec3_length(lhs);
}

float vec2_distanceSq(Vec2 lhs, Vec2 rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return vec2_lengthSq(lhs);
}

float vec3_distanceSq(Vec3 lhs, Vec3 rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return vec3_lengthSq(lhs);
}

Vec2 vec2_lerp(Vec2 lhs, Vec2 rhs, float t)
{
    return (Vec2){lerp(lhs.x, rhs.x, t), lerp(lhs.y, rhs.y, t)};
}

Vec3 vec3_lerp(Vec3 lhs, Vec3 rhs, float t)
{
    return (Vec3){lerp(lhs.x, rhs.x, t), lerp(lhs.y, rhs.y, t), lerp(lhs.z, rhs.z, t)};
}

Vec4 vec4_lerp(Vec4 lhs, Vec4 rhs, float t)
{
    return (Vec4){lerp(lhs.x, rhs.x, t), lerp(lhs.y, rhs.y, t), lerp(lhs.z, rhs.z, t), lerp(lhs.w, rhs.w, t)};
}

Vec2 vec2_mul(Vec2 lhs, Vec2 rhs)
{
    return (Vec2){lhs.x * rhs.x, lhs.y * rhs.y};
}

Vec3 vec3_mul(Vec3 lhs, Vec3 rhs)
{
    return (Vec3){lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

Vec4 vec4_mul(Vec4 lhs, Vec4 rhs)
{
    return (Vec4){lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w};
}

Vec2 vec2_add(Vec2 lhs, Vec2 rhs)
{
    return (Vec2){lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec3 vec3_add(Vec3 lhs, Vec3 rhs)
{
    return (Vec3){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

Vec4 vec4_add(Vec4 lhs, Vec4 rhs)
{
    return (Vec4){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
}

Vec2 vec2_sub(Vec2 lhs, Vec2 rhs)
{
    return (Vec2){lhs.x - rhs.x, lhs.y - rhs.y};
}

Vec3 vec3_sub(Vec3 lhs, Vec3 rhs)
{
    return (Vec3){lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

Vec4 vec4_sub(Vec4 lhs, Vec4 rhs)
{
    return (Vec4){lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
}

Vec2 vec2_div(Vec2 lhs, Vec2 rhs)
{
    return (Vec2){lhs.x / rhs.x, lhs.y / rhs.y};
}

Vec3 vec3_div(Vec3 lhs, Vec3 rhs)
{
    return (Vec3){lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

Vec4 vec4_div(Vec4 lhs, Vec4 rhs)
{
    return (Vec4){lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w};
}

float vec2_dot(Vec2 lhs, Vec2 rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

float vec3_dot(Vec3 lhs, Vec3 rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

float vec4_dot(Vec4 lhs, Vec4 rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

Vec3 vec3_cross(Vec3 lhs, Vec3 rhs)
{
    Vec3 cross;
    cross.x = lhs.y * rhs.z - lhs.z * rhs.y;
    cross.y = lhs.x * rhs.z - lhs.z * rhs.x;
    cross.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return cross;
}

void vec2_normalize(Vec2 *v)
{
    float n = 1.0f / sqrtf(v->x * v->x + v->y * v->y);
    v->x *= n;
    v->y *= n;
}

void vec3_normalize(Vec3 *v)
{
    float n = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x *= n;
    v->y *= n;
    v->z *= n;
}

void vec4_normalize(Vec4 *v)
{
    float n = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
    v->x *= n;
    v->y *= n;
    v->z *= n;
    v->w *= n;
}

void quat_normalize(Quaternion *q)
{
    float qn = 1.0f / sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
    q->x *= qn;
    q->y *= qn;
    q->z *= qn;
    q->w *= qn;
}

void quat_invert(Quaternion *q)
{
    float n2 = (q->x * q->x) +
               (q->y * q->y) +
               (q->z * q->z) +
               (q->w * q->w);

    float n = 1.0f / n2;
    q->x *= -n;
    q->y *= -n;
    q->z *= -n;
    q->w *= n;
}

Vec3 vec3_transformQuat(Quaternion q, Vec3 v)
{
    float x = 2 * (q.y * v.z - q.z * v.y);
    float y = 2 * (q.z * v.x - q.x * v.z);
    float z = 2 * (q.x * v.y - q.y * v.x);

    float rX = v.x + x * q.w + (q.y * z - q.z * y);
    float rY = v.y + y * q.w + (q.z * x - q.x * z);
    float rZ = v.z + z * q.w + (q.x * y - q.y * x);

    return (Vec3){rX, rY, rZ};
}

Quaternion quat_mul(Quaternion lhs, Quaternion rhs)
{
    float x = lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y + lhs.w * rhs.x;
    float y = -lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x + lhs.w * rhs.y;
    float z = lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w + lhs.w * rhs.z;
    float w = -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z + lhs.w * rhs.w;

    return (Quaternion){x, y, z, w};
}

Quaternion quat_fromEuler(Vec3 eulerAngles)
{
    Quaternion q;

    float cx = cosf(eulerAngles.x * 0.5);
    float sx = sinf(eulerAngles.x * 0.5);
    float cy = cosf(eulerAngles.y * 0.5);
    float sy = sinf(eulerAngles.y * 0.5);
    float cz = cosf(eulerAngles.z * 0.5);
    float sz = sinf(eulerAngles.z * 0.5);

    q.w = cx * cy * cz + sx * sy * sz;
    q.x = sx * cy * cz - cx * sy * sz;
    q.y = cx * sy * cz + sx * cy * sz;
    q.z = cx * cy * sz - sx * sy * cz;

    return q;
}

Vec4 vec4_transform(Mat4 mat, Vec4 vec)
{
    float x = (vec.x * mat.m[0][0]) + (vec.y * mat.m[1][0]) + (vec.z * mat.m[2][0]) + (vec.w * mat.m[3][0]);
    float y = (vec.x * mat.m[0][1]) + (vec.y * mat.m[1][1]) + (vec.z * mat.m[2][1]) + (vec.w * mat.m[3][1]);
    float z = (vec.x * mat.m[0][2]) + (vec.y * mat.m[1][2]) + (vec.z * mat.m[2][2]) + (vec.w * mat.m[3][2]);
    float w = (vec.x * mat.m[0][3]) + (vec.y * mat.m[1][3]) + (vec.z * mat.m[2][3]) + (vec.w * mat.m[3][3]);

    return (Vec4){x, y, z, w};
}

Mat4 mat4_translate(Vec3 translation)
{
    Mat4 mat = MAT4_IDENTITY;
    mat.m[3][0] = translation.x;
    mat.m[3][1] = translation.y;
    mat.m[3][2] = translation.z;
    return mat;
}

Mat4 mat4_scale(Vec3 scale)
{
    Mat4 mat = MAT4_IDENTITY;
    mat.m[0][0] = scale.x;
    mat.m[1][1] = scale.y;
    mat.m[2][2] = scale.z;
    return mat;
}

Mat4 mat4_rotation(Quaternion q)
{
    Mat4 mat = MAT4_IDENTITY;

    mat.m[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
    mat.m[0][1] = 2.0f * q.x * q.y - 2.0f * q.z * q.w;
    mat.m[0][2] = 2.0f * q.x * q.z + 2.0f * q.y * q.w;

    mat.m[1][0] = 2.0f * q.x * q.y + 2.0f * q.z * q.w;
    mat.m[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
    mat.m[1][2] = 2.0f * q.y * q.z - 2.0f * q.x * q.w;

    mat.m[2][0] = 2.0f * q.x * q.z - 2.0f * q.y * q.w;
    mat.m[2][1] = 2.0f * q.y * q.z + 2.0f * q.x * q.w;
    mat.m[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;

    return mat;
}

Mat4 mat4_projectionOrtho(float left, float right, float top, float bottom, float near, float far)
{
    float scale_x = 2.0f / (right - left);
    float scale_y = 2.0f / (top - bottom);
    float scale_z = 1.0f / (near - far);

    Mat4 mat = MAT4_IDENTITY;

    mat.m[0][0] = scale_x;
    mat.m[1][1] = scale_y;
    mat.m[2][2] = scale_z;

    mat.m[3][0] = (left + right) / (left - right);
    mat.m[3][1] = (top + bottom) / (bottom - top);
    mat.m[3][2] = near / (near - far);

    return mat;
}

Mat4 mat4_projectionOrthoAspect(float aspectRatio, float scale, float near, float far)
{
    float extentX = scale * aspectRatio * 0.5f;
    float extentY = scale * 0.5f;

    return mat4_projectionOrtho(-extentX, extentX, extentY, -extentY, near, far);
}

Mat4 mat4_projectionPerspective(float aspectRatio, float fieldOfView, float near, float far)
{
    float top = tanf(fieldOfView * 0.5f) * near;
    float bottom = -top;
    float right = top * aspectRatio;
    float left = -right;

    float height = top - bottom;
    float width = right - left;

    float two_n = 2.0f * near;

    Mat4 mat;

    mat.m[0][0] = two_n / width;
    mat.m[0][1] = mat.m[0][2] = mat.m[0][3] = 0.0f;
    mat.m[1][1] = two_n / height;
    mat.m[1][0] = mat.m[1][2] = mat.m[1][3] = 0.0f;
    mat.m[2][2] = far / (near - far);
    mat.m[2][0] = mat.m[2][1] = 0.0f;
    mat.m[2][3] = -1.0f;
    mat.m[3][0] = mat.m[3][1] = mat.m[3][3] = 0.0f;
    mat.m[3][2] = ((near * far) /
                   (near - far));

    return mat;
}

// multiply two matrices together
Mat4 mat4_mul(Mat4 lhs, Mat4 rhs)
{
    Mat4 mat;

    mat.m[0][0] = (lhs.m[0][0] * rhs.m[0][0]) + (lhs.m[0][1] * rhs.m[1][0]) + (lhs.m[0][2] * rhs.m[2][0]) + (lhs.m[0][3] * rhs.m[3][0]);
    mat.m[0][1] = (lhs.m[0][0] * rhs.m[0][1]) + (lhs.m[0][1] * rhs.m[1][1]) + (lhs.m[0][2] * rhs.m[2][1]) + (lhs.m[0][3] * rhs.m[3][1]);
    mat.m[0][2] = (lhs.m[0][0] * rhs.m[0][2]) + (lhs.m[0][1] * rhs.m[1][2]) + (lhs.m[0][2] * rhs.m[2][2]) + (lhs.m[0][3] * rhs.m[3][2]);
    mat.m[0][3] = (lhs.m[0][0] * rhs.m[0][3]) + (lhs.m[0][1] * rhs.m[1][3]) + (lhs.m[0][2] * rhs.m[2][3]) + (lhs.m[0][3] * rhs.m[3][3]);

    mat.m[1][1] = (lhs.m[1][0] * rhs.m[0][1]) + (lhs.m[1][1] * rhs.m[1][1]) + (lhs.m[1][2] * rhs.m[2][1]) + (lhs.m[1][3] * rhs.m[3][1]);
    mat.m[1][2] = (lhs.m[1][0] * rhs.m[0][2]) + (lhs.m[1][1] * rhs.m[1][2]) + (lhs.m[1][2] * rhs.m[2][2]) + (lhs.m[1][3] * rhs.m[3][2]);
    mat.m[1][3] = (lhs.m[1][0] * rhs.m[0][3]) + (lhs.m[1][1] * rhs.m[1][3]) + (lhs.m[1][2] * rhs.m[2][3]) + (lhs.m[1][3] * rhs.m[3][3]);
    mat.m[1][0] = (lhs.m[1][0] * rhs.m[0][0]) + (lhs.m[1][1] * rhs.m[1][0]) + (lhs.m[1][2] * rhs.m[2][0]) + (lhs.m[1][3] * rhs.m[3][0]);

    mat.m[2][0] = (lhs.m[2][0] * rhs.m[0][0]) + (lhs.m[2][1] * rhs.m[1][0]) + (lhs.m[2][2] * rhs.m[2][0]) + (lhs.m[2][3] * rhs.m[3][0]);
    mat.m[2][1] = (lhs.m[2][0] * rhs.m[0][1]) + (lhs.m[2][1] * rhs.m[1][1]) + (lhs.m[2][2] * rhs.m[2][1]) + (lhs.m[2][3] * rhs.m[3][1]);
    mat.m[2][2] = (lhs.m[2][0] * rhs.m[0][2]) + (lhs.m[2][1] * rhs.m[1][2]) + (lhs.m[2][2] * rhs.m[2][2]) + (lhs.m[2][3] * rhs.m[3][2]);
    mat.m[2][3] = (lhs.m[2][0] * rhs.m[0][3]) + (lhs.m[2][1] * rhs.m[1][3]) + (lhs.m[2][2] * rhs.m[2][3]) + (lhs.m[2][3] * rhs.m[3][3]);

    mat.m[3][0] = (lhs.m[3][0] * rhs.m[0][0]) + (lhs.m[3][1] * rhs.m[1][0]) + (lhs.m[3][2] * rhs.m[2][0]) + (lhs.m[3][3] * rhs.m[3][0]);
    mat.m[3][1] = (lhs.m[3][0] * rhs.m[0][1]) + (lhs.m[3][1] * rhs.m[1][1]) + (lhs.m[3][2] * rhs.m[2][1]) + (lhs.m[3][3] * rhs.m[3][1]);
    mat.m[3][2] = (lhs.m[3][0] * rhs.m[0][2]) + (lhs.m[3][1] * rhs.m[1][2]) + (lhs.m[3][2] * rhs.m[2][2]) + (lhs.m[3][3] * rhs.m[3][2]);
    mat.m[3][3] = (lhs.m[3][0] * rhs.m[0][3]) + (lhs.m[3][1] * rhs.m[1][3]) + (lhs.m[3][2] * rhs.m[2][3]) + (lhs.m[3][3] * rhs.m[3][3]);

    return mat;
}

void mat4_loadIdentitySIMD()
{
    Mat4 m = MAT4_IDENTITY;
    mat4_loadSIMD(&m);
}