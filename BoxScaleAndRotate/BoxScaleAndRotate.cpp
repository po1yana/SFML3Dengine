#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>
#include "vec.h"
#include "matrix.h"

float radToDeg(float rad) {
    return rad * 180.f / M_PI;
}

float degToRad(float deg) {
    return deg * M_PI / 180.f;
}

class camera {
public:
    float aspectRatio = 1280.f / 720.f; // получение автоматического размера окна SFML + функция перерисовки при ресайзе
    vec3 cameraPos;
    float Pitch = degToRad(0);
    float Yaw = degToRad(0);
    
    vec3 axisX = {cos(Yaw), 0 , -sin(Yaw)};
    vec3 axisY = {sin(Yaw) * sin(Pitch), cos(Pitch), cos(Yaw) * sin(Pitch)};
    vec3 axisZ = {sin(Yaw) * cos(Pitch), -sin(Pitch), cos(Pitch) * cos(Yaw)};
    
    mat4 viewMatrix = {
       vec4(axisX[0],            axisY[0],            axisZ[0],      0),
       vec4(axisX[1],            axisY[1],            axisZ[1],      0),
       vec4(axisX[2],            axisY[2],            axisZ[2],      0),
       vec4(-dot(axisX, cameraPos), -dot(axisY, cameraPos), -dot(axisZ, cameraPos), 1)
    };

    float nPlane, fPlane, fovY;
    float fovX = 2 * atan(tan(fovY * 0.5) * aspectRatio);

    std::vector <std::vector <float>> nPlaneMatrix;
    std::vector <std::vector <float>> fPlaneMatrix;

    float nHalfDimX = nPlane * tan(fovX / 2);
    float nHalfDimY = nPlane * tan(fovY / 2);
    float fHalfDimX = fPlane * tan(fovX / 2);
    float fHalfDimY = fPlane * tan(fovY / 2);

    void setPosition(vec3 _newPos) {
        cameraPos = _newPos;
    }
    std::vector <std::vector <float>> getNearPlaneMatrix() {
        return nPlaneMatrix;
    }
    std::vector <std::vector <float>> getFarPlaneMatrix() {
        return fPlaneMatrix;
    }
    void updateCamera() { // реализация описана на базе позиционирования камеры в глобальных координатах
        nPlaneMatrix = {
            {cameraPos[0] - nHalfDimX,  cameraPos[1] + nHalfDimY, cameraPos[2] - nPlane},
            {cameraPos[0] + nHalfDimX,  cameraPos[1] + nHalfDimY, cameraPos[2] - nPlane },
            {cameraPos[0] + nHalfDimX,  cameraPos[1] - nHalfDimY, cameraPos[2] - nPlane },
            {cameraPos[0] - nHalfDimX,  cameraPos[1] - nHalfDimY, cameraPos[2] - nPlane }
        };

        fPlaneMatrix = {
            {cameraPos[0] - fHalfDimX / 2,  cameraPos[1] + fHalfDimY / 2, cameraPos[2] - fPlane},
            {cameraPos[0] + fHalfDimX / 2,  cameraPos[1] + fHalfDimY / 2, cameraPos[2] - fPlane},
            {cameraPos[0] + fHalfDimX / 2,  cameraPos[1] - fHalfDimY / 2, cameraPos[2] - fPlane},
            {cameraPos[0] - fHalfDimX / 2,  cameraPos[1] - fHalfDimY / 2, cameraPos[2] - fPlane},
        };
    }
    void printCameraData() {
        std::cout << "Camera-pos: " << cameraPos[0] << "," << cameraPos[1] << "," << cameraPos[2] << std::endl
            << "FovY than FovX: " << radToDeg(fovY) <<  " " << radToDeg(fovX) << " CameraFrustumMatrix: " << std::endl;

        for (int i = 0; i < 4; i++) { 
            for (int j = 0; j < 3; j++) {
                std::cout << nPlaneMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl; 
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << fPlaneMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    camera(vec3 _cameraPos, float _nPlane, float _fPlane, float _fovYdeg) : cameraPos(_cameraPos), nPlane(_nPlane), fPlane(_fPlane), fovY(degToRad(_fovYdeg))
    {
        updateCamera();
    };
};

struct plane
{
    sf::Vector3f vertice1, vertice2, vertice3, vertice4;
    plane(sf::Vector3f _vert1, sf::Vector3f _vert2, sf::Vector3f _vert3, sf::Vector3f _vert4) :
        vertice1(_vert1), vertice2(_vert2) , vertice3(_vert3) , vertice4(_vert4) {};

};

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Default, settings);
    sf::Vertex vertices[] =
    {
        sf::Vertex(sf::Vector2f(0,   0), sf::Color::Red, sf::Vector2f(0,  0)),
        sf::Vertex(sf::Vector2f(0, 100), sf::Color::Blue, sf::Vector2f(0, 10)),
        sf::Vertex(sf::Vector2f(100, 100), sf::Color::Green, sf::Vector2f(10, 10)),
        sf::Vertex(sf::Vector2f(100,   0), sf::Color::White, sf::Vector2f(10,  0))
    };

    vec3 CameraStartPos(0, 0, 0);
    camera mainCamera(CameraStartPos, 0.1, 100, 60);
    mainCamera.printCameraData();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(vertices, 4, sf::Triangles);
        window.display();
    }

    return 0;
}
