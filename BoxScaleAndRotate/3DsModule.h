#pragma once
#include <SFML/Graphics.hpp>
#include "3dsMath.h"
#include "3DsRasterizer.h"
#include "3DsVertex.h"
#include "3DsCamera.h"
#include "3DsPrimitive.h"
#include <vector>

const int windowHeight = 720;
const int windowWidth = 720;
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML-3Ds v1");

std::vector <Primitive> objectsList;
int counterObjectsOnScene = 0;
std::vector <Vertex> vBuffer;
float ZBUFFER[windowWidth * windowHeight];
sf::VertexArray BITBUFFER;

Camera *mainCamera;
bool DRAWPOLYGONS = true;

void initZBUFFER() {
	for (int i = 0; i < windowHeight; i++)
	{
		for (int j = 0; j < windowWidth; j++)
		{
			ZBUFFER[i * windowWidth + j] = INFINITY;
		}
	}
}

void initCamera(sf::Vector2u _win, float _nPlane, float _fPlane, float _fovYdeg, typeCamera _type) {
	mainCamera = new Camera(_win, _nPlane, _fPlane, _fovYdeg);
}

void initPrimitive(const vec3(&_vArray)[], const vec3(&_cArray)[], typePrimitive _type) {
	switch (_type)
	{
	case TRIANGLE:
		objectsList.push_back(Triangle(_vArray, _cArray));
		counterObjectsOnScene += 1;
		break;
	case PLANE:
		objectsList.push_back(Plane(_vArray, _cArray));
		counterObjectsOnScene += 1;
		break;
	default:
		break;
	}
}

void drawTriangle(vec3* _vertexArray, sf::Color _color = sf::Color::White) {
	rasterizeTrinagle(window, &BITBUFFER, ZBUFFER, _vertexArray, _color);
}

void drawObject(Primitive _object) {
	if (_object.type == TRIANGLE) {
		vec3 MVP[] = {
			mainCamera->vShader(_object.vertexArray[_object.indexArray[0]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[1]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[2]])
		};
		drawTriangle(MVP, sf::Color::White);
	}
	if (_object.type == PLANE) {
		vec3 MVP[] = {
			mainCamera->vShader(_object.vertexArray[_object.indexArray[0]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[1]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[2]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[5]])
		};
		//if ((MVP[0][2] > 10 && MVP[1][2] > 10 && MVP[2][2] > 10) || 
		//	(MVP[0][2] < 1 && MVP[1][2] < 1 && MVP[2][2] < 1)) {
		//}

		drawTriangle(new vec3[3]{MVP[0],MVP[1], MVP[2]}, sf::Color::Red);
		drawTriangle(new vec3[3]{MVP[0],MVP[2], MVP[3] }, sf::Color::White);
	}
}

void windowClose() {
	window.close();
}

bool windowIsOpen() {
	return window.isOpen();
}

void windowDraw() {
	window.draw(BITBUFFER);
}

void drawAll() {
	for (int i = 0; i < counterObjectsOnScene; i++) {
		drawObject(objectsList[i]);
	}
	windowDraw();
}

void windowClear() {
	window.clear();
	initZBUFFER();
	BITBUFFER.clear();
}

void windowDisplay() {
	window.display();
}

bool windowPollEvent(sf::Event &_event) {
	return window.pollEvent(_event);
}

void updateScene() {
	window.clear();
}

void initScene() {
	initZBUFFER();
}