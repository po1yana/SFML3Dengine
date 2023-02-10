#pragma once
#include <SFML/Graphics.hpp>
#include "3DsModule.h"
#include "3dsMath.h"

void rasterizeTrinagle(sf::RenderWindow &_window, sf::VertexArray *_BITBUFFER, float* _ZBUFFER, vec3* _vertexArray, sf::Color _color = sf::Color::White) {
    sortVec3(_vertexArray, 3, S_SORT_BY_Y);
    float dx13 = 0, dx12 = 0, dx23 = 0;
    float dz13 = 0, dz12 = 0, dz23 = 0;
    float _dz13 = 0, _dz12 = 0, _dz23 = 0;
    float ZValue;

    if (_vertexArray[2][1] != _vertexArray[0][1]) {
        dx13 = _vertexArray[2][0] - _vertexArray[0][0];
        dx13 /= _vertexArray[2][1] - _vertexArray[0][1];
        dz13 = (_vertexArray[2][2] - _vertexArray[0][2]) / (_vertexArray[2][1] - _vertexArray[0][1]);
    }
    else { dx13 = 0; dz13 = 0; }

    if (_vertexArray[1][1] != _vertexArray[0][1]) {
        dx12 = _vertexArray[1][0] - _vertexArray[0][0];
        dx12 /= _vertexArray[1][1] - _vertexArray[0][1];
        dz12 = (_vertexArray[1][2] - _vertexArray[0][2]) / (_vertexArray[1][1] - _vertexArray[0][1]);
    }
    else { dx12 = 0; dz12 = 0; }

    if (_vertexArray[2][1] != _vertexArray[1][1]) {
        dx23 = _vertexArray[2][0] - _vertexArray[1][0];
        dx23 /= _vertexArray[2][1] - _vertexArray[1][1];
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

    std::cout << (int)_color.g << std::endl;
    //_vertexArray[0].debugPrint();
    //_vertexArray[1].debugPrint();
    //_vertexArray[2].debugPrint();

    for (int i = (int)_vertexArray[0][1]; i < (int)_vertexArray[1][1]; i++) {
        // draw upper tris by points
        if (i < 720 && i >= 0) {
            _dz12 = _vertexArray[0][2] + dz12 * (i - (int)_vertexArray[0][1]);
            _dz13 = _vertexArray[0][2] + dz13 * (i - (int)_vertexArray[0][1]);
            for (int j = (int)wx1; j <= (int)wx2; j++) {
                if (j <= 720 && j >= 0) {
                    if ((wx2 - wx1) == 0) {
                        ZValue = _dz13;
                    }
                    else ZValue = _dz13 + (((_dz12 - _dz13) / (wx2 - wx1)) * (j - (int)wx1));
                    if (1 <= ZValue && ZValue <= 10) {
                        if (ZValue <= _ZBUFFER[j + (i * 720)]) {
                            _ZBUFFER[j + (i * 720)] = ZValue;
                            sf::Vertex vert(sf::Vector2f(j, i), sf::Color(_color.r * (1 - ((ZValue - 1) / 9)), _color.g * (1 - ((ZValue - 1) / 9)), _color.b * (1 - ((ZValue - 1) / 9))));
                            _BITBUFFER->append(vert);
                        }
                    }
                }
            };
        }
        wx1 += dx13;
        wx2 += dx12;
     }
     std::cout << wx1 << "  " << wx2 << std::endl;
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
            if (swap) {
                _dz13 = _vertexArray[0][2] + dz23 * (i - (int)_vertexArray[0][1]);
                _dz23 = _vertexArray[1][2] + _bdz13 * (i - (int)_vertexArray[1][1]);
            }
            else {
                _dz23 = _vertexArray[0][2] + _bdz13 * (i - (int)_vertexArray[0][1]);
                _dz13 = _vertexArray[1][2] + dz23 * (i - (int)_vertexArray[1][1]);
            }
            for (int j = (int)wx1; j <= (int)wx2; j++) {
                if (j <= 720 && j >= 0) {
                    if ((wx2 - wx1) == 0) {
                        ZValue = _dz23;
                    }
                    else ZValue = _dz23 + (((_dz13 - _dz23) / (wx2 - wx1)) * (j - (int)wx1));
                    if (1 <= ZValue && ZValue <= 10) {
                        if (ZValue < _ZBUFFER[j + (i * 720)]) {
                            _ZBUFFER[j + (i * 720)] = ZValue;
                            sf::Vertex vert(sf::Vector2f(j, i), sf::Color(_color.r * (1 - ((ZValue - 1) / 9)), _color.g * (1 - ((ZValue - 1) / 9)), _color.b * (1 - ((ZValue - 1) / 9))));
                            _BITBUFFER->append(vert);
                        }
                    }
                }
            }
        }
        wx1 += _dx13;
        wx2 += dx23;
    }
}