#ifndef _VEC3_H
#define _VEC3_H

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

Vec3 addByVec3(Vec3 v1, Vec3 v2);
Vec3 subByVec3(Vec3 v1, Vec3 v2);
Vec3 mulByVec3(Vec3 v1, Vec3 v2);
Vec3 divByVec3(Vec3 v1, Vec3 v2);
Vec3 mulByScale(Vec3 v1, float value);

Vec3 addByVec3(Vec3 v1, Vec3 v2)
{
    Vec3 v = {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };
    return v;
}

Vec3 subByVec3(Vec3 v1, Vec3 v2)
{
    Vec3 v = {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    };
    return v;
}

Vec3 mulByVec3(Vec3 v1, Vec3 v2)
{
    Vec3 v = {
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z
    };
    return v;
}

Vec3 divByVec3(Vec3 v1, Vec3 v2)
{
    Vec3 v = {
        v1.x / v2.x,
        v1.y / v2.y,
        v1.z / v2.z
    };
    return v;
}
Vec3 mulByScale(Vec3 v1, float value)
{
    Vec3 v = {
        v1.x *value,
        v1.y *value,
        v1.z *value
    };
    return v;
}
#endif