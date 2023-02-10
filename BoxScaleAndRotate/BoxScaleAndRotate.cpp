//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//
//#define _USE_MATH_DEFINES
//#include <math.h>
//#include "3dsMath.h"
//
//float RADTODEG(float rad) {
//    return rad * 180.f / M_PI;
//}
//
//float DEGTORAD(float deg) {
//    return deg * M_PI / 180.f;
//}
//
//class camera {
//public:
//    void debugVertexRastData(sf::Vector2f _rVertex) {
//        std::cout << "X: " << _rVertex.x << " Y: " << _rVertex.y << std::endl;
//    }
//
//    float aspectRatio = 1280.0f / 720.0f; // получение автоматического размера окна SFML + функция перерисовки при ресайзе
//    float wVieport = 1280.0f;
//    float hVieport = 720.0f;
//    vec3 cameraPos;
//    vec3 right, up, forward;
//    float Roll = 0;
//    float Pitch = 0;
//    float Yaw = 0;
//    
//    mat4 viewMatrix;
//    mat4 projectionMatrix;
//
//    float nPlane, fPlane, fovY;
//    float fovX = 2 * atan(tan(fovY * 0.5) * aspectRatio);
//
//    std::vector <std::vector <float>> nPlaneMatrix;
//    std::vector <std::vector <float>> fPlaneMatrix;
//
//    float nHalfDimX = nPlane * tan(fovX / 2);
//    float nHalfDimY = nPlane * tan(fovY / 2);
//    float fHalfDimX = fPlane * tan(fovX / 2);
//    float fHalfDimY = fPlane * tan(fovY / 2);
//
//    void setPosition(vec3 _newPos) {
//        cameraPos = _newPos;
//    }
//    std::vector <std::vector <float>> getNearPlaneMatrix() {
//        return nPlaneMatrix;
//    }
//    std::vector <std::vector <float>> getFarPlaneMatrix() {
//        return fPlaneMatrix;
//    }
//
//    mat4 setFrustum(float l, float r, float b, float t, float n, float f)
//    {
//        mat4 matrix;
//       /* matrix = {
//            vec4((2 * n) / (r - l), 0,               (r + l) / (r - l),        0),
//            vec4(0,                 2 * n / (t - b), (t + b) / (t - b),        0),
//            vec4(0,                 0,               -(f + n) / (f - n),       -(2 * f * n) / (f - n)),
//            vec4(0,                 0,               -1,                       0)
//        };*/
//        
//        matrix = {
//           vec4((2 * n) / (r - l), 0,                   0,                      0),
//           vec4(0,                 2 * n / (t - b),     0,                      0),
//           vec4((r + l) / (r - l), (t + b) / (t - b),  -(f + n) / (f - n),      -1),
//           vec4(0,                 0,                  -(2 * f * n) / (f - n),  0)
//        };
//        return matrix;
//    }
//
//    mat4 setFrustum(float fovY, float aspectRatio, float front, float back)
//    {
//        float tangent = tan(fovY / 2);
//        float height = front * tangent;
//        float width = height * aspectRatio; 
//
//        /*std::cout << "HEIGHT: " << height << " WIDTH: " << width << "   AR: " << aspectRatio << std::endl;*/
//        return setFrustum(-width, width, -height, height, front, back);
//    }
//
//    void setModelView(float _x, float _y, float _z) {
//        _x = DEGTORAD(_x); _y = -DEGTORAD(_y); _z = DEGTORAD(_z);
//        std::cout << _x << std::endl;
//        /*viewMatrix = mat4(
//            vec4(cos(_y) * cos(_z), -cos(_y)*sin(_z), sin(_y), cameraPos[0]),
//            vec4(sin(_x) * sin(_y) * cos(_z) + cos(_x) * sin(_z), -sin(_x) * sin(_y) * sin(_z) + cos(_x) * cos(_z), -sin(_x) * cos(_y), cameraPos[1]),
//            vec4(-cos(_x) * sin(_y) * cos(_z) + sin(_x) * sin(_z), cos(_x) * sin(_y) * sin(_z) + sin(_x) * cos(_z), cos(_x) * cos(_y), cameraPos[2]),
//            vec4(0, 0, 0, 1)
//        );*/
//        viewMatrix = mat4(
//            vec4(cos(_y) * cos(_z), sin(_x) * sin(_y) * cos(_z) + cos(_x) * sin(_z), -cos(_x) * sin(_y) * cos(_z) + sin(_x) * sin(_z), 0),
//            vec4(-cos(_y) * sin(_z), -sin(_x) * sin(_y) * sin(_z) + cos(_x) * cos(_z), cos(_x) * sin(_y) * sin(_z) + sin(_x) * cos(_z), 0),
//            vec4(sin(_y), -sin(_x) * cos(_y), cos(_x) * cos(_y), 0),
//            vec4(-cameraPos[0], -cameraPos[1], -cameraPos[2], 1)
//        );
//    }
//
//    vec3 clip2NDC(vec4 _matClip) {
//        return vec3(_matClip[0]/_matClip[3], _matClip[1] / _matClip[3], _matClip[2] / _matClip[3]);
//    }
//
//    vec3 NDC2Win(vec3 _matNDC) {
//        return vec3(
//            (wVieport / 2) * -_matNDC[0] + (-1 + (wVieport/2)),
//            (hVieport / 2) * _matNDC[1] + (-1 + (hVieport/2)), 
//            ((fPlane - nPlane)/2 * _matNDC[2] + ((fPlane + nPlane)/2))
//        );
//    }
//
//    sf::Vector2f vec3SFML(vec3 _matWin) {
//        return sf::Vector2f(_matWin[0], _matWin[1]);
//    }
//
//    vec3 SFMLvec3(sf::Vector2f _dVertex, float _z) {
//        return vec3(_dVertex.x, _dVertex.y, _z);
//    }
//
//    sf::Vector2f vertexRast(vec3 _dVertex) {
//        /*std::cout << " vec3: ";
//        _dvertex.debugprint();
//
//        std::cout << "vec4: ";
//        vec4(_dvertex, 1.f).debugprint();
//
//        std::cout << "viewmat4" << std::endl;
//        viewmatrix.debugprint();
//
//        std::cout << std::endl<< "eyespace: ";
//        (viewmatrix * vec4(_dvertex, 1.f)).debugprint();
//
//        std::cout << std::endl << "clipspace: ";*/
//
//        vec4 MVP = projectionMatrix * (viewMatrix * vec4(_dVertex, 1.0f));
//        MVP[3] = fabs(MVP[3]) * -1;
//
//        /*MVP.debugPrint();
//
//        std::cout << std::endl << "NDC: ";
//        (clip2NDC(projectionMatrix * (viewMatrix * vec4(_dVertex, 1.f)))).debugPrint();
//
//        std::cout << std::endl << "WINspace: ";
//        (NDC2Win(clip2NDC(projectionMatrix * (viewMatrix * vec4(_dVertex, 1.f))))).debugPrint();*/
//
//        sf::Vector2f debugVertex = vec3SFML((NDC2Win(clip2NDC(MVP))));
//
//        return debugVertex;
//    }
//
//    void updateCamera() { // реализация описана на базе позиционирования камеры в глобальных координатах
//    }
//
//    void initCamera() {
//        projectionMatrix = setFrustum(fovY, aspectRatio, nPlane, fPlane);
//        /*projectionMatrix = setFrustum(-0.5, 0.5, -0.5, 0.5, 1, 10); */
//        setModelView(Roll,Pitch,0);
//       /* viewMatrix.debugPrint();
//        projectionMatrix.debugPrint();*/
//        updateCamera();
//    }
//
//    void debugPrintCameraData() {
//        std::cout << "Camera-pos: " << cameraPos[0] << "," << cameraPos[1] << "," << cameraPos[2] << std::endl
//            << "FovY than FovX: " << RADTODEG(fovY) <<  " " << RADTODEG(fovX) << std::endl;
//    }
//
//    camera(vec3 _cameraPos, float _nPlane, float _fPlane, float _fovYdeg) : cameraPos(_cameraPos), nPlane(_nPlane), fPlane(_fPlane), fovY(DEGTORAD(_fovYdeg))
//    {
//        initCamera();
//    };
//};
//
//struct plane
//{
//    sf::Vector3f vertice1, vertice2, vertice3, vertice4;
//    plane(sf::Vector3f _vert1, sf::Vector3f _vert2, sf::Vector3f _vert3, sf::Vector3f _vert4) :
//        vertice1(_vert1), vertice2(_vert2) , vertice3(_vert3) , vertice4(_vert4) {};
//
//};
//
//int main231()
//{
//    float hAngle = 0,vAngle = 0;
//    float mouseSence = 1;
//
//    sf::ContextSettings settings;
//    settings.antialiasingLevel = 8;
//    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Default, settings);
//    window.setFramerateLimit(100);
//    sf::Clock clock;
//
//    vec3 p1(-1, 1, 2);
//    vec3 p2(1, 1, 2);
//    vec3 p3(1, -1, 2);
//    vec3 p4(-1, -1, 2);
//
//    vec3 CameraStartPos(0, 0, 0);
//    camera mainCamera(CameraStartPos, 1, 50, 60);
//    mainCamera.debugPrintCameraData();
//
//    bool keyQuery[4] = { 0,0,0,0 };
//
//   sf::Vertex vertices[] =
//    {
//        sf::Vertex(mainCamera.vertexRast(p1), sf::Color::Red, sf::Vector2f(0,  0)),
//        sf::Vertex(mainCamera.vertexRast(p2), sf::Color::Blue, sf::Vector2f(0, 10)),
//        sf::Vertex(mainCamera.vertexRast(p3), sf::Color::Green, sf::Vector2f(10, 10)),
//        sf::Vertex(mainCamera.vertexRast(p4), sf::Color::White, sf::Vector2f(10,  0))
//    };
//
//   bool delta = false;
//    while (window.isOpen())
//    {
//        sf::Time elapsedTime = clock.getElapsedTime();
//
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (event.type == sf::Event::KeyPressed)
//            {
//                if (event.key.code == sf::Keyboard::Escape)
//                {
//                    window.close();
//                }
//                if (event.key.code == sf::Keyboard::W)
//                {
//                    keyQuery[0] = true;
//                }
//                if (event.key.code == sf::Keyboard::S)
//                {
//                    keyQuery[1] = true;
//                }
//                if (event.key.code == sf::Keyboard::A)
//                {
//                    keyQuery[2] = true;
//                }
//                if (event.key.code == sf::Keyboard::D)
//                {
//                    keyQuery[3] = true;
//                }
//                if (event.key.code == sf::Keyboard::Q)
//                {
//                    mainCamera.Pitch -= 1;
//                }
//                if (event.key.code == sf::Keyboard::E)
//                {
//                    mainCamera.Pitch += 1;
//                }
//            }
//            if (event.type == sf::Event::KeyReleased)
//            {
//                if (event.key.code == sf::Keyboard::W)
//                {
//                    keyQuery[0] = false;
//                }
//                if (event.key.code == sf::Keyboard::S)
//                {
//                    keyQuery[1] = false;
//                }
//                if (event.key.code == sf::Keyboard::A)
//                {
//                    keyQuery[2] = false;
//                }
//                if (event.key.code == sf::Keyboard::D)
//                {
//                    keyQuery[3] = false;
//                }
//            }
//
//            if (event.type == sf::Event::MouseMoved)
//            {
//                delta = true;
//
//               /* std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
//               std::cout << "new mouse y: " << event.mouseMove.y << std::endl;*/
//            }
//            hAngle += mouseSence * elapsedTime.asSeconds() * float(1280 / 2 - event.mouseMove.x);
//            vAngle += mouseSence * elapsedTime.asSeconds() * float(720 / 2 - event.mouseMove.y);
//            mainCamera.Roll += vAngle;
//            mainCamera.Pitch -= hAngle;
//
//            /*std::cout << hAngle << std::endl;*/
//        }
//
//        
//
//        if (keyQuery[0]) {
//            mainCamera.cameraPos[2] += 4 * elapsedTime.asSeconds();
//            delta = true;
//        }
//        if (keyQuery[1]) {
//            mainCamera.cameraPos[2] -= 4 * elapsedTime.asSeconds();
//            delta = true;
//        }
//        if (keyQuery[2]) {
//            mainCamera.cameraPos[0] -= 4 * elapsedTime.asSeconds();
//            delta = true;
//        }
//        if (keyQuery[3]) {
//            mainCamera.cameraPos[0] += 4 * elapsedTime.asSeconds();
//            delta = true;
//        }
//        
//
//        if (delta) {
//            mainCamera.initCamera();
//            vertices[0] = sf::Vertex(mainCamera.vertexRast(p1), sf::Color::Red, sf::Vector2f(0, 0));
//            vertices[1] = sf::Vertex(mainCamera.vertexRast(p2), sf::Color::Blue, sf::Vector2f(0, 0));
//            vertices[2] = sf::Vertex(mainCamera.vertexRast(p3), sf::Color::Green, sf::Vector2f(0, 0));
//            vertices[3] = sf::Vertex(mainCamera.vertexRast(p4), sf::Color::White, sf::Vector2f(0, 0));
//        }
//        
//        /*std::cout << elapsedTime.asSeconds() << std::endl;*/
//        sf::Mouse::setPosition(sf::Vector2i((int)1280 / 2, (int)720 / 2), window);
//        clock.restart().asSeconds();
//
//        window.clear(sf::Color::Black);
//        window.draw(vertices, 4, sf::Quads);
//        window.display();
//        delta = false;
//        hAngle = vAngle = 0;
//    }
//
//    return 0;
//}
