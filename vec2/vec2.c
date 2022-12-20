#include "vec2.h"

vec2 vec2_new(double x, double y) {
    vec2 v = { x, y };
    return v;
}

vec2 vec2_add(vec2 a, vec2 b) {
    return vec2_new(a.x + b.x, a.y + b.y);
}

vec2 vec2_sub(vec2 a, vec2 b) {
    return vec2_new(a.x - b.x, a.y - b.y);
}

vec2 vec2_mul(vec2 v, double s) {
    return vec2_new(v.x * s, v.y * s);
}

double vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

double vec2_len(vec2 v) {
    return sqrt(vec2_dot(v, v));
}

vec2 vec2_normalize(vec2 v) {
    double len = vec2_len(v);
    if (len == 0) {
        return vec2_new(0, 0);
    }
    else {
        return vec2_mul(v, 1.0 / len);
    }
}