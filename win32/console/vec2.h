#ifndef _VEC2_H
#define _VEC2_H
typedef struct Vec2 {
    float x;
    float y;
} Vec2;

Vec2 addByVec2(Vec2 v1, Vec2 v2);
Vec2 subByVec2(Vec2 v1, Vec2 v2);
Vec2 mulByVec2(Vec2 v1, Vec2 v2);
Vec2 divByVec2(Vec2 v1, Vec2 v2);
Vec2 addByValue(Vec2 v1, float value);
Vec2 subByValue(Vec2 v1, float value);
Vec2 mulByValue(Vec2 v1, float value);
Vec2 divByValue(Vec2 v1, float value);

inline Vec2 addByVec2(Vec2 v1, Vec2 v2)
{
    Vec2 r = {
        v1.x + v2.x,
        v2.y + v2.y
    };
    return r;
}

inline Vec2 subByVec2(Vec2 v1, Vec2 v2)
{
    Vec2 r = {
        v1.x - v2.x,
        v2.y - v2.y
    };
    return r;
}

inline Vec2 mulByVec2(Vec2 v1, Vec2 v2)
{
    Vec2 r = {
        v1.x * v2.x,
        v1.y * v2.y
    };
    return r;
}

inline Vec2 divByVec2(Vec2 v1, Vec2 v2)
{
    Vec2 r = {
        v1.x / v2.x,
        v1.y / v2.y
    };
    return r;
}

inline Vec2 aaddByValuedd(Vec2 v1, float value) {
    Vec2 r = {
        v1.x + value,
        v1.y + value
    };
    return r;
}
inline Vec2 subByValue(Vec2 v1, float value) {
    Vec2 r = {
        v1.x - value,
        v1.y - value
    };
    return r;
}
inline Vec2 mulByValue(Vec2 v1, float value) {
    Vec2 r = {
        v1.x * value,
        v1.y * value
    };
    return r;
}
inline Vec2 divByValue(Vec2 v1, float value) {
    Vec2 r = {
        v1.x / value,
        v1.y / value
    };
    return r;
}

#endif