#include <math.h>
#include "vec2.h"
#include "vec3.h"

float clamp(float value, float min, float max) { return fmax(fmin(value, max), min);}

float length(Vec2 const v) { return sqrt(v.x * v.x + v.y * v.y);}

float length3d(Vec3 const v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);}

Vec3 norm(Vec3 v) { 
    float l = length3d(v);
    Vec3 r = {
        v.x / l,
        v.y / l,
        v.z / l
    };
    return r;
}

float dot(Vec3 const a, Vec3 const b) {
    return a.x* b.x + a.y*b.y + a.z * b.z;    
};

Vec2 sphere(Vec3 ro, Vec3 rd, float r) {
    float b = dot(ro, rd);
    float c = dot(ro, ro) - r * r;
    float h = b * b - c;
    
    if (h < 0.0) {
        Vec2 rv = {
            -1.0f,
            -1.0f,
            -1.0f
        };
        return rv;
    }
    h = sqrt(h);
    Vec2 rv = {
        (-b - h), // length
        (-b + h) // ?
    };
    return rv;
}
