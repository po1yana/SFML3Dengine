#pragma once
#include <SFML/Graphics.hpp>
#include "3DsModule.h"
#include "3dsMath.h"

void rasterizeTrinagle(sf::RenderWindow &_window, sf::Uint8 *_BITBUFFER, float* _ZBUFFER, vec3* _vertexArray, sf::Color _color = sf::Color::White) {
    sortVec3(_vertexArray, 3, S_SORT_BY_Y);
    float dx13 = 0, dx12 = 0, dx23 = 0;
    float dz13 = 0, dz12 = 0, dz23 = 0;
    float _dz13 = 0, _dz12 = 0, _dz23 = 0;
    float ZValue;

    float x1 = _vertexArray[0][0], y1 = _vertexArray[0][1], z1 = (_vertexArray[0][2] - 1) / 9;
    float x2 = _vertexArray[1][0], y2 = _vertexArray[1][1], z2 = (_vertexArray[1][2] - 1) / 9;
    float x3 = _vertexArray[2][0], y3 = _vertexArray[2][1], z3 = (_vertexArray[2][2] - 1) / 9;

    float a = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
    float b = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
    float c = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    float d = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));

    if (_vertexArray[2][1] != _vertexArray[0][1]) {
        dx13 = _vertexArray[2][0] - _vertexArray[0][0];
        dx13 /= (int)_vertexArray[2][1] - (int)_vertexArray[0][1];
        dz13 = (_vertexArray[2][2] - _vertexArray[0][2]) / (_vertexArray[2][1] - _vertexArray[0][1]);
    }
    else { dx13 = 0; dz13 = 0; }

    if (_vertexArray[1][1] != _vertexArray[0][1]) {
        dx12 = _vertexArray[1][0] - _vertexArray[0][0];
        dx12 /= (int)_vertexArray[1][1] - (int)_vertexArray[0][1];
        dz12 = (_vertexArray[1][2] - _vertexArray[0][2]) / (_vertexArray[1][1] - _vertexArray[0][1]);
    }
    else { dx12 = 0; dz12 = 0; }

    if (_vertexArray[2][1] != _vertexArray[1][1]) {
        dx23 = _vertexArray[2][0] - _vertexArray[1][0];
        dx23 /= (int)_vertexArray[2][1] - (int)_vertexArray[1][1];
        dz23 = (_vertexArray[2][2] - _vertexArray[1][2]) / (_vertexArray[2][1] - _vertexArray[1][1]);
    }
    else { dx23 = 0; dz23 = 0; }


    float wx1 = _vertexArray[0][0];
    float wx2 = wx1;
    float _dx13 = dx13;
    float _bdz13 = dz13;

    if (dx13 > dx12)
    {
        swapF(dx12, dx13);
        swapF(dz12, dz13);
    };

    std::cout << (-(a * 100) - (b * _vertexArray[1][1]) - d) / c << std::endl;
    std::cout << (-(a * 200) - (b * _vertexArray[1][1]) - d) / c << std::endl << std::endl;
    for (int i = (int)_vertexArray[0][1]; i < (int)_vertexArray[1][1]; i++) {
        // draw upper tris by points
        if (i < 720 && i >= 0) {
            for (int j = (int)wx1; j <= (int)wx2; j++) {
                if (j < 720 && j >= 0) {

                    ZValue = (-(a * j) - (b * i) - d) / c;

                    if (0 <= ZValue && ZValue <= 1) {
                        if (ZValue < _ZBUFFER[j + (i * 720)]) {
                            _ZBUFFER[j + (i * 720)] = ZValue;
                            _BITBUFFER[(j + (i * 720)) * 4] = 255;
                            _BITBUFFER[(j + (i * 720)) * 4 + 1] = 255;
                            _BITBUFFER[(j + (i * 720)) * 4 + 2] = 255;
                            _BITBUFFER[(j + (i * 720)) * 4 + 3] = _color.a;
                        }
                    }
                }
            };
        }
        wx1 += dx13;
        wx2 += dx12;
    }

    if (_vertexArray[0][1] == _vertexArray[1][1]) {
        wx1 = _vertexArray[0][0];
        wx2 = _vertexArray[1][0];
    }

    bool swap = false;
    if (_dx13 < dx23)
    {
        swapF(_dx13, dx23);
        swapF(_bdz13, dz23);
        swap = true;
    }

    for (int i = (int)_vertexArray[1][1]; i <= (int)_vertexArray[2][1]; i++) {
        if (i < 720 && i >= 0) {
            for (int j = (int)wx1; j <= (int)wx2; j++) {
                if (j < 720 && j >= 0) {
                    ZValue = (-(a * j) - (b * i) - d) / c;

                    if (0 <= ZValue && ZValue <= 1) {
                        if (ZValue < _ZBUFFER[j + (i * 720)]) {
                            _ZBUFFER[j + (i * 720)] = ZValue;
                            _BITBUFFER[(j + (i * 720)) * 4] = _color.r ;
                            _BITBUFFER[(j + (i * 720)) * 4 + 1] = _color.g;
                            _BITBUFFER[(j + (i * 720)) * 4 + 2] = _color.b;
                            _BITBUFFER[(j + (i * 720)) * 4 + 3] = _color.a;
                        }
                    }
                }
            }
        }
        wx1 += _dx13;
        wx2 += dx23;
    }
}


//_dz12 = _vertexArray[0][2] + dz12 * (i - (int)_vertexArray[0][1]);
//_dz13 = _vertexArray[0][2] + dz13 * (i - (int)_vertexArray[0][1]);

//if ((wx2 - wx1) == 0) {
                  //    ZValue = _dz13;
                  //}
                  //else ZValue = _dz13 + (((_dz12 - _dz13) / (wx2 - wx1)) * (j - (int)wx1));





      //if ((wx2 - wx1) == 0) {
                    //    ZValue = _dz23;
                    //}
                    //else ZValue = _dz23 + (((_dz13 - _dz23) / (wx2 - wx1)) * (j - (int)wx1));



//if (swap) {
//    _dz13 = _vertexArray[0][2] + dz23 * (i - (int)_vertexArray[0][1]);
//    _dz23 = _vertexArray[1][2] + _bdz13 * (i - (int)_vertexArray[1][1]);
//}
//else {
//    _dz23 = _vertexArray[0][2] + _bdz13 * (i - (int)_vertexArray[0][1]);
//    _dz13 = _vertexArray[1][2] + dz23 * (i - (int)_vertexArray[1][1]);
//}