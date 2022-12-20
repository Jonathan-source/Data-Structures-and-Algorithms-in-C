#ifndef VEC2_H
#define VEC2_H

#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} vec2;

vec2 vec2_new(double x, double y);

vec2 vec2_add(vec2 a, vec2 b);

vec2 vec2_sub(vec2 a, vec2 b);

vec2 vec2_mul(vec2 v, double s);

double vec2_dot(vec2 a, vec2 b);

double vec2_len(vec2 v);

vec2 vec2_normalize(vec2 v);

#endif // VEC2_H
