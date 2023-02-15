#pragma once
#include "3dsMath.h"
#include "3DsVertex.h"

typedef enum {
	TRIANGLE,
	PLANE,
	CUBE
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
		this->indexArray = new int[6]
		{ 
			0, 1, 2,
			0, 2, 3 
		};
	}
};


class Cube : public Primitive
{
public:
	Cube(const vec3(&_vArray)[], const vec3(&_cArray)[]) {
		this->vertexArray = _vArray;
		this->colorArray = _cArray;
		this->type = CUBE;
		this->indexArray = new int[36]
		{
			0, 1, 2, // front
			0, 2, 3,

			4, 5, 6, // back
			4, 6, 7,

			4, 0, 3, // left
			4, 3, 7,

			1, 5, 6, // right
			1, 6, 2, 

			4, 5, 1, // top
			4, 1, 0,

			7, 6, 2, // bottom
			7, 2, 3
		};
	}
};
