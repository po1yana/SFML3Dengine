#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>
#include "3dsMath.h"
#include "3DsCamera.h"
#include "3DsModule.h"


int wHeight = 720;
int wWidth = 720;


sf::Vector2f vec3SFML(vec3 _matWin) {
    return sf::Vector2f(_matWin[0], _matWin[1]);
}

vec3 SFMLvec3(sf::Vector2f _dVertex, float _z) {
    return vec3(_dVertex.x, _dVertex.y, _z);
}

int main()
{
    initScene();

    initCamera(window.getSize(), 1, 10, 60, PERSPECTIVE);

    //mainCamera.DEBUGprintParams();

    initPrimitive(
        {
           vec3(9, -1, 0),
           vec3(5, -1, -4),
           vec3(1, -1, 0),
           vec3(5, -1, 4),
        },
        {
           vec3(0, 255, 0)
        },
        PLANE
    );

    //initPrimitive(
    //    {
    //       vec3(3, 2, 1),
    //       vec3(3, 2, -1),
    //       vec3(3, 0, -1),
    //       vec3(3, 0, 1),

    //       vec3(5, 2, 1),
    //       vec3(5, 2, -1),
    //       vec3(5, 0, -1),
    //       vec3(5, 0, 1)
    //    },
    //    {
    //       vec3(255, 0, 0),
    //       vec3(0, 255, 0),
    //       vec3(0, 0, 255),
    //       vec3(255, 255, 255),
    //       vec3(0, 255, 255),
    //       vec3(255, 0, 255)
    //    },
    //    CUBE
    //);


    windowClear();
    drawAll();
    windowDisplay();

    window.setMouseCursorVisible(false);

    sf::Clock clock;
    bool keyQuery[4] = { 0,0,0,0 };
    bool delta = false;
    float hAngle = 0;
    float vAngle = 0;

    while (windowIsOpen())
    {
        sf::Time elapsedTime = clock.getElapsedTime();
        clock.restart().asSeconds();

        sf::Event event;
        while (windowPollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windowClose();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    keyQuery[0] = true;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    keyQuery[1] = true;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    keyQuery[2] = true;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    keyQuery[3] = true;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    keyQuery[0] = false;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    keyQuery[1] = false;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    keyQuery[2] = false;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    keyQuery[3] = false;
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                hAngle += 0.1 * elapsedTime.asSeconds() * float(720 / 2 - event.mouseMove.x);
                vAngle += 0.1 * elapsedTime.asSeconds() * float(720 / 2 - event.mouseMove.y);
                mainCamera->yaw += hAngle;
                mainCamera->pitch += vAngle;
                delta = true;
            }
        }
        if (keyQuery[0]) {
            mainCamera->position = mainCamera->position + mainCamera->direction * (5 * elapsedTime.asSeconds());
            delta = true;
        }
        if (keyQuery[1]) {
            mainCamera->position = mainCamera->position - mainCamera->direction * (5 * elapsedTime.asSeconds());
            delta = true;
        }
        if (keyQuery[2]) {
            mainCamera->position = mainCamera->position - mainCamera->right * (5 * elapsedTime.asSeconds());
            delta = true;
        }
        if (keyQuery[3]) {
            mainCamera->position = mainCamera->position + mainCamera->right  * (5 * elapsedTime.asSeconds());
            delta = true;
        }

        if (delta) {
            mainCamera->update();
            windowClear();
            drawAll();
            windowDisplay();
            //mainCamera->DEBUGprintPosition();
        }
        
        sf::Mouse::setPosition(sf::Vector2i((int)720 / 2, (int)720 / 2), window);
        hAngle = vAngle = 0;
        delta = false;

    }

    return 0;
}

//sf::RenderWindow window(sf::VideoMode(720, 720), "SFML-3Ds v1");
//
//initCamera(window.getSize(), 1, 100, 60, PERSPECTIVE);
//
//vec3 p1(-1, 1, 2);
//vec3 p2(1, 1, 2);
//vec3 p3(1, -1, 2);
//vec3 p4(-1, -1, 2);
//
//vec3 p5(-1, 1, 4);
//vec3 p6(1, 1, 4);
//vec3 p7(1, -1, 1);
//vec3 p8(-1, -1, 1);
//
//vec3 p9(-1, 1, 4);
//vec3 p10(1, 1, 4);
//vec3 p11(1, 1, 2);
//vec3 p12(-1, 1, 2);
//
//sf::Vertex vertices[] =
//{
//    sf::Vertex(mainCamera.vShader(p1), sf::Color::Red, sf::Vector2f(0,  0)),
//    sf::Vertex(mainCamera.vShader(p2), sf::Color::Blue, sf::Vector2f(0, 10)),
//    sf::Vertex(mainCamera.vShader(p3), sf::Color::Green, sf::Vector2f(10, 10)),
//    sf::Vertex(mainCamera.vShader(p4), sf::Color::White, sf::Vector2f(10,  0))
//};
//
//sf::Vertex vertices1[] =
//{
//    sf::Vertex(mainCamera.vShader(p5), sf::Color::Red, sf::Vector2f(0,  0)),
//    sf::Vertex(mainCamera.vShader(p6), sf::Color::Blue, sf::Vector2f(0, 10)),
//    sf::Vertex(mainCamera.vShader(p7), sf::Color::Green, sf::Vector2f(10, 10)),
//    sf::Vertex(mainCamera.vShader(p8), sf::Color::White, sf::Vector2f(10,  0))
//};
//
//window.setFramerateLimit(100);
//window.setMouseCursorVisible(false);
//sf::Clock clock;
//bool keyQuery[4] = { 0,0,0,0 };
//float hAngle = 0;
//float vAngle = 0;
//bool delta = false;
//
//while (window.isOpen())
//{
//    sf::Time elapsedTime = clock.getElapsedTime();
//    /* mainCamera.DEBUGprintParams();*/
//
//    sf::Event event;
//    while (window.pollEvent(event))
//    {
//        if (event.type == sf::Event::Closed)
//            window.close();
//        if (event.type == sf::Event::KeyPressed)
//        {
//            if (event.key.code == sf::Keyboard::Escape)
//            {
//                window.close();
//            }
//            if (event.key.code == sf::Keyboard::W)
//            {
//                keyQuery[0] = true;
//            }
//            if (event.key.code == sf::Keyboard::S)
//            {
//                keyQuery[1] = true;
//            }
//            if (event.key.code == sf::Keyboard::A)
//            {
//                keyQuery[2] = true;
//            }
//            if (event.key.code == sf::Keyboard::D)
//            {
//                keyQuery[3] = true;
//            }
//        }
//        if (event.type == sf::Event::KeyReleased)
//        {
//            if (event.key.code == sf::Keyboard::W)
//            {
//                keyQuery[0] = false;
//            }
//            if (event.key.code == sf::Keyboard::S)
//            {
//                keyQuery[1] = false;
//            }
//            if (event.key.code == sf::Keyboard::A)
//            {
//                keyQuery[2] = false;
//            }
//            if (event.key.code == sf::Keyboard::D)
//            {
//                keyQuery[3] = false;
//            }
//        }
//
//        if (event.type == sf::Event::MouseMoved)
//        {
//            hAngle += 0.01 * elapsedTime.asSeconds() * float(720 / 2 - event.mouseMove.x);
//            vAngle += 0.01 * elapsedTime.asSeconds() * float(720 / 2 - event.mouseMove.y);
//            mainCamera.yaw += hAngle;
//            mainCamera.pitch += vAngle;
//            delta = true;
//        }
//    }
//
//    if (keyQuery[0]) {
//        mainCamera.position[2] += 4 * elapsedTime.asSeconds();
//        delta = true;
//    }
//    if (keyQuery[1]) {
//        mainCamera.position[2] -= 4 * elapsedTime.asSeconds();
//        delta = true;
//    }
//    if (keyQuery[2]) {
//        mainCamera.position[0] -= 4 * elapsedTime.asSeconds();
//        delta = true;
//    }
//    if (keyQuery[3]) {
//        mainCamera.position[0] += 4 * elapsedTime.asSeconds();
//        delta = true;
//    }
//
//
//    if (delta) {
//        mainCamera.update();
//        /*mainCamera.DEBUGprintParams();*/
//        vertices[0] = sf::Vertex(mainCamera.vShader(p1), sf::Color::Red, sf::Vector2f(0, 0));
//        vertices[1] = sf::Vertex(mainCamera.vShader(p2), sf::Color::Red, sf::Vector2f(0, 0));
//        vertices[2] = sf::Vertex(mainCamera.vShader(p3), sf::Color::Red, sf::Vector2f(0, 0));
//        vertices[3] = sf::Vertex(mainCamera.vShader(p4), sf::Color::Red, sf::Vector2f(0, 0));
//
//        vertices1[0] = sf::Vertex(mainCamera.vShader(p5), sf::Color::Blue, sf::Vector2f(0, 0));
//        vertices1[1] = sf::Vertex(mainCamera.vShader(p6), sf::Color::Blue, sf::Vector2f(0, 0));
//        vertices1[2] = sf::Vertex(mainCamera.vShader(p7), sf::Color::Blue, sf::Vector2f(0, 0));
//        vertices1[3] = sf::Vertex(mainCamera.vShader(p8), sf::Color::Blue, sf::Vector2f(0, 0));
//    }
//
//    sf::Mouse::setPosition(sf::Vector2i((int)720 / 2, (int)720 / 2), window);
//    clock.restart().asSeconds();
//
//    window.clear();
//    window.draw(vertices1, 4, sf::Quads);
//    window.draw(vertices, 4, sf::Quads);
//    window.display();
//    /*system("CLS");*/
//    delta = false;
//    hAngle = vAngle = 0;
//}
