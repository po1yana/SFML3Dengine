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
sf::Uint8* BITBUFFER = new sf::Uint8[windowHeight * windowWidth * 4];
sf::Texture CURRENTFRAME;

//sf::VertexArray BITBUFFER;

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

void clearBITBUFFER() {
	for (register int i = 0; i < 720 * 720 * 4; i += 4) {
		BITBUFFER[i] = 0;
		BITBUFFER[i + 1] = 0;
		BITBUFFER[i + 2] = 0;
		BITBUFFER[i + 3] = 255;
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
	case CUBE:
		objectsList.push_back(Cube(_vArray, _cArray));
		counterObjectsOnScene += 1;
		break;
	default:
		break;
	}
}

void drawTriangle(vec3* _vertexArray, sf::Color _color = sf::Color::White) {
	rasterizeTrinagle(window, BITBUFFER, ZBUFFER, _vertexArray, _color);
}

void drawObject(Primitive _object) {
	if (_object.type == TRIANGLE) {
		vec3 MVP[] = {
			mainCamera->vShader(_object.vertexArray[_object.indexArray[0]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[1]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[2]])
		};
		drawTriangle(MVP, sf::Color(
			(int)_object.colorArray[0][0],
			(int)_object.colorArray[0][1],
			(int)_object.colorArray[0][2]
		));
	}
	if (_object.type == PLANE) {
		vec3 MVP[] = {
			mainCamera->vShader(_object.vertexArray[_object.indexArray[0]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[1]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[2]]),
			mainCamera->vShader(_object.vertexArray[_object.indexArray[5]])
		};
		drawTriangle(new vec3[3]{MVP[0],MVP[1], MVP[2]}, sf::Color::Red);
		drawTriangle(new vec3[3]{MVP[0],MVP[2], MVP[3] }, sf::Color(
			(int)_object.colorArray[0][0],
			(int)_object.colorArray[0][1],
			(int)_object.colorArray[0][2]
		));
	}

	if (_object.type == CUBE) {
		vec3 MVP[] = {
			mainCamera->vShader(_object.vertexArray[0]),
			mainCamera->vShader(_object.vertexArray[1]),
			mainCamera->vShader(_object.vertexArray[2]),
			mainCamera->vShader(_object.vertexArray[3]),
			mainCamera->vShader(_object.vertexArray[4]),
			mainCamera->vShader(_object.vertexArray[5]),
			mainCamera->vShader(_object.vertexArray[6]),
			mainCamera->vShader(_object.vertexArray[7])
		};
		for (int i = 0; i < 36; i += 6) {
			drawTriangle(new vec3[3]
			{
				MVP[_object.indexArray[i]],
				MVP[_object.indexArray[i + 1]],
				MVP[_object.indexArray[i + 2]]
			}, 
			sf::Color(
				(int)_object.colorArray[i/6][0],
				(int)_object.colorArray[i/6][1],
				(int)_object.colorArray[i/6][2]
			));
			drawTriangle(new vec3[3]
			{
				MVP[_object.indexArray[i + 3]],
				MVP[_object.indexArray[i + 4]],
				MVP[_object.indexArray[i + 5]]
			},
			sf::Color(
				(int)_object.colorArray[i / 6][0],
				(int)_object.colorArray[i / 6][1],
				(int)_object.colorArray[i / 6][2]
			));
		}
	}
}

void windowClose() {
	window.close();
}

bool windowIsOpen() {
	return window.isOpen();
}

void windowDraw() {
	CURRENTFRAME.update(BITBUFFER);
	sf::Sprite sprite(CURRENTFRAME);
	window.draw(sprite);
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
	clearBITBUFFER();
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
	CURRENTFRAME.create(windowWidth, windowHeight);
}