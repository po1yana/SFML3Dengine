#pragma once
#include "matrix.h"

struct vec3
{
    float values[3];
  
    vec3()
    {
        values[0] = values[1] = values[2] = 0;
    }

    vec3(float x, float y, float z)
    {
        values[0] = x;
        values[1] = y;
        values[2] = z;
    }

    const float& operator[] (int index) const
    {
        return values[index];
    }
    float& operator[] (int index)
    {
        return values[index];
    }
};

float dot(vec3 a, vec3 b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

struct vec4
{
    float values[4];

    vec4()
    {
        values[0] = values[1] = values[2] = values[3] = 0;
    }

    vec4(float x, float y, float z, float w)
    {
        values[0] = x;
        values[1] = y;
        values[2] = z;
        values[3] = w;
    }

    const float& operator[] (int index) const
    {
        return values[index];
    }
    float& operator[] (int index)
    {
        return values[index];
    }
};

vec4 operator*(const mat4& m, const vec4& v)
{
    return vec4(
        m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
        m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
        m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
        m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
    );
}

vec4 operator*(const vec4& v, const mat4& m)
{
    return vec4(
        v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3],
        v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3],
        v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3],
        v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]
    );
}