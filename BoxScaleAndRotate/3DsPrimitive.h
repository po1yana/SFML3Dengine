#pragma once
#include "3dsMath.h"
#include "3DsVertex.h"

typedef enum {
	TRIANGLE,
	PLANE,
} typePrimitive;

class Primitive
{
public:
	const vec3* vertexArray;
	const vec3* colorArray;
	const int* indexArray;
	int type;
};


class Triangle : public Primitive
{
public:
	Triangle(const vec3(&_vArray)[], const vec3(&_cArray)[]) {
		this->vertexArray = _vArray;
		this->colorArray = _cArray;
		this->type = TRIANGLE;
		this->indexArray = new int[3]{0, 1, 2};
	}
};

class Plane : public Primitive
{
public:
	Plane(const vec3(&_vArray)[], const vec3(&_cArray)[]) {
		this->vertexArray = _vArray;
		this->colorArray = _cArray;
		this->type = PLANE;
		this->indexArray = new int[6]{ 0, 1, 2, 0, 2, 3 };
	}
};
