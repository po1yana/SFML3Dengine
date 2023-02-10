#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

void swapF(float& a, float& b) {
    float c = a; a = b; b = c;
}

void swapI(int& a, int& b) {
    float c = a; a = b; b = c;
}

float RADTODEG(float rad) {
    return rad * 180.f / M_PI;
}

float DEGTORAD(float deg) {
    return deg * M_PI / 180.f;
}

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
    void debugPrint() {
        for (int i = 0; i < 3; i++) {
            std::cout << values[i] << " ";
        }
        std::cout << std::endl;
    }
};

void swapVec3(vec3& a, vec3& b) {
    vec3 c = a; a = b; b = c;
}

float lenght(vec3 a) {
    return sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
}

vec3 normalize(vec3 a) {
    float aLen = lenght(a);
    return vec3(a[0] / aLen, a[1] / aLen, a[2] / aLen);
}

float dot(vec3 a, vec3 b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

vec3 cross(vec3 a, vec3 b) {
    return vec3(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}

typedef enum {
    S_SORT_BY_X,
    S_SORT_BY_Y,
    S_SORT_BY_Z
} sortingByValue;

void sortVec3(vec3* _vertexArray, int _arraySize, sortingByValue _type) {
    bool inSort = true;
    while (inSort) {
        inSort = false;
        for (int i = 1; i < _arraySize; i++) {
            if (_vertexArray[i][_type] < _vertexArray[i - 1][_type]) {
                inSort = true;
                swapVec3(_vertexArray[i], _vertexArray[i - 1]);
            }
        }
    }
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

    vec4(vec3 _vec, float w)
    {
        values[0] = _vec[0];
        values[1] = _vec[1];
        values[2] = _vec[2];
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
    void debugPrint() {
        for (int i = 0; i < 4; i++) {
            std::cout << values[i] << " ";
        }
        std::cout << std::endl;
    }
};

struct mat4
{
    vec4 rows[4];

    mat4()
    {
        rows[0] = vec4(1, 0, 0, 0);
        rows[1] = vec4(0, 1, 0, 0);
        rows[2] = vec4(0, 0, 1, 0);
        rows[3] = vec4(0, 0, 0, 1);
    }

    mat4(vec4 x, vec4 y, vec4 z, vec4 w)
    {
        rows[0] = x;
        rows[1] = y;
        rows[2] = z;
        rows[3] = w;
    }

    const vec4& operator[](int index) const
    {
        return rows[index];
    }
    vec4& operator[](int index)
    {
        return rows[index];
    }
    void debugPrint() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << rows[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

mat4 operator*(const mat4& m1, const mat4& m2)
{
    vec4 X(
        m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0],
        m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1],
        m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2],
        m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3]
    );
    vec4 Y(
        m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0],
        m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1],
        m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2],
        m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3]
    );
    vec4 Z(
        m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0],
        m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1],
        m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2],
        m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3]
    );
    vec4 W(
        m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0],
        m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1],
        m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2],
        m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3]
    );

    return mat4(X, Y, Z, W);
}

vec4 operator*(const mat4& m, const vec4& v)
{
    return vec4(
        m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
        m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
        m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
        m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
    );
}

vec4 operator*(const vec4& v, const mat4& m)
{
    return vec4(
       v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + v[3] * m[3][0],
       v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + v[3] * m[3][1],
       v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + v[3] * m[3][2],
       v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + v[3] * m[3][3]
    );
}