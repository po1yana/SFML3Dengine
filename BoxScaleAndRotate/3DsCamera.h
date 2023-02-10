#pragma once
#include <SFML/Graphics.hpp>
#include "3dsMath.h"
//DEBUG HEADERS
#include <iostream>

typedef enum {
    ORTO,
    PERSPECTIVE,
} typeCamera;

class Camera
{
public:
	sf::Vector2f win;
	vec3 position;
	vec3 forward, right, up;
	float nPlane, fPlane, fovX, fovY;
    float pitch, yaw, roll; 
	float aspectRatio = (float)win.x / (float)win.y;

    vec3 direction;

	mat4 viewMatrix;
    mat4 viewMatrixBA;
	mat4 projectionMatrix;

    void setModelView(float _x, float _y, float _z) {
        /*_x = DEGTORAD(_x); _y = -DEGTORAD(_y); _z = DEGTORAD(_z);*/
        viewMatrixBA = mat4(
            vec4(cos(_y) * cos(_z), -cos(_y)*sin(_z), sin(_y), position[0]),
            vec4(sin(_x) * sin(_y) * cos(_z) + cos(_x) * sin(_z), -sin(_x) * sin(_y) * sin(_z) + cos(_x) * cos(_z), -sin(_x) * cos(_y), position[1]),
            vec4(-cos(_x) * sin(_y) * cos(_z) + sin(_x) * sin(_z), cos(_x) * sin(_y) * sin(_z) + sin(_x) * cos(_z), cos(_x) * cos(_y), position[2]),
            vec4(0, 0, 0, 1)
        );
    }

    void setModelView() {
        /*mat4 rot(
            vec4(right[0], right[1], right[1], 0),
            vec4(up[0], up[1], up[2], 0),
            vec4(forward[0], forward[1], forward[2], 0),
            vec4(0, 0, 0, 1)
        );
        mat4 pos(
            vec4(1, 0, 0, -position[0]),
            vec4(0, 1, 0, -position[1]),
            vec4(0, 0, 1, -position[2]),
            vec4(0, 0, 0,            1)
        );*/
        up = vec3(0, 1, 0);
        right = normalize(cross(up, direction));
        up = cross(direction, right);

        mat4 rot(
            vec4(right[0], right[1], right[2], 0),
            vec4(up[0],    up[1],    up[2],    0),
            vec4(direction[0], direction[1], direction[2], 0),
            vec4(0,0,0,1)
        );
        mat4 pos(
            vec4(1, 0, 0,  -position[0]),
            vec4(0, 1, 0,  -position[1]),
            vec4(0, 0, 1,  -position[2]),
            vec4(0, 0, 0,  1)
        );
        viewMatrix = rot * pos;
    }

    void setFrustum(float l, float r, float b, float t, float n, float f)
    {
        /*projectionMatrix = {
             vec4((2 * n) / (r - l), 0,               (r + l) / (r - l),        0),
             vec4(0,                 2 * n / (t - b), (t + b) / (t - b),        0),
             vec4(0,                 0,               -1 * ((f + n) / (f - n)),       (-2 * f * n) / (f - n)),
             vec4(0,                 0,               -1,                       0)
        };*/
        projectionMatrix = {
             vec4((2 * n) / (r - l), 0,               (r + l) / (r - l),        0),
             vec4(0,                 2 * n / (t - b), (t + b) / (t - b),        0),
             vec4(0,                 0,               -(f + n) / (n - f),       (-2 * f * n) / (n - f)),
             vec4(0,                 0,               1,                       0)
        };
    }

    void setFrustum(float fovY, float aspectRatio, float front, float back)
    {
        float tangent = tan(fovY / 2);
        float height = front * tangent;
        float width = height * aspectRatio;
        setFrustum(-width, width, -height, height, front, back);
    }

    vec3 clip2NDC(vec4 _matClip) {
        return vec3(_matClip[0] / _matClip[3], _matClip[1] / _matClip[3], _matClip[2] / _matClip[3]);
    }

    vec3 NDC2Win(vec3 _matNDC) {
        return vec3(
            (win.x / 2) * -_matNDC[0] + (-1 + (win.x / 2)),
            (win.y / 2) * _matNDC[1] + (-1 + (win.y / 2)),
            (((fPlane - nPlane) / 2) * _matNDC[2] + ((fPlane + nPlane) / 2))
        );
    }

    sf::Vector2f vec3SFML(vec3 _matWin) {
        return sf::Vector2f(_matWin[0], _matWin[1]);
    }

    vec3 SFMLvec3(sf::Vector2f _dVertex, float _z) {
        return vec3(_dVertex.x, _dVertex.y, _z);
    }

    vec3 vShader(vec3 _dVertex) {
        float scale = win.x / (2 * nPlane * tan(fovX / 2)); // winx
        vec4 local = viewMatrix * vec4(_dVertex, 1.0f);

        float delta;
        if (local[2] < 0) {
            delta = nPlane / -local[2] * scale;
        }
        else delta = nPlane / local[2] * scale;
        vec3 projection(local[0] * delta, local[1] * delta, local[2]);
        vec3 screen(projection[0] + (win.x / 2), projection[1] + (-win.y / 2), projection[2]);
        vec3 screenCoords(screen[0], -screen[1], screen[2]);

        //screenCoords.debugPrint();
        return screenCoords;
    }

    void init() {
        setFrustum(fovY, aspectRatio, nPlane, fPlane);
        roll = pitch = yaw = 0;
        yaw = DEGTORAD(1.2343);
        fovX = 2 * atan(tan(fovY * 0.5) * aspectRatio);
        setModelView(pitch, yaw, roll);


        direction[0] = cos(pitch) * cos(yaw);
        direction[1] = sin(pitch);
        direction[2] = cos(pitch) * sin(yaw);
        direction = normalize(direction);

        setModelView();

    }

    void update() {
        setModelView(pitch, yaw, roll);
        direction[0] = cos(pitch) * cos(yaw);
        direction[1] = sin(pitch);
        direction[2] = cos(pitch) * sin(yaw);
        direction = normalize(direction);

        setModelView();
    }
    Camera() {};

	Camera(sf::Vector2u _win, float _nPlane, float _fPlane, float _fovYdeg) : win(_win), position(vec3(0,0,0)), nPlane(_nPlane), fPlane(_fPlane), fovY(DEGTORAD(_fovYdeg))
	{
        init();
	};

	Camera(sf::Vector2u _win, vec3 _cameraPos, float _nPlane, float _fPlane, float _fovYdeg) : win(_win), position(_cameraPos), nPlane(_nPlane), fPlane(_fPlane), fovY(DEGTORAD(_fovYdeg))
	{
        init();
	};





    //DEBUG FIELD NOT FOR RELEASED V
    void DEBUGprintParams(){
        std::cout << "WIN X  |  Y: " << win.x << "  " << win.y << std::endl;
        std::cout << "aspectRatio: " << aspectRatio << std::endl;
        std::cout << "Nplane dist | Fplane dist  " << nPlane << "  " << fPlane << std::endl;
        std::cout << "Position: "; position.debugPrint(); std::cout<<std::endl;
        std::cout << "Angles (X / Y / Z): "; std::cout << RADTODEG(pitch) << "/" << RADTODEG(yaw) << "/" << RADTODEG(roll) << std::endl;
        std::cout << "DIRECTION vector: "; direction.debugPrint(); std::cout << std::endl;
        std::cout << "RIGHT vector: "; right.debugPrint(); std::cout << std::endl;
        std::cout << "UP vector: "; up.debugPrint(); std::cout << std::endl;
        viewMatrix.debugPrint();
        projectionMatrix.debugPrint();
        std::cout << "MODEL IGNORED" << std::endl;
    }
    void DEBUGprintPosition() {
        std::cout << "Position: "; position.debugPrint(); std::cout << std::endl;
    }
};
