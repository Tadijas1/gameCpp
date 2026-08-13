#pragma once
#include <raylib.h>

class Laser
{
    Vector2 posicion;
    Color color;
    float speed;

    public:
    Laser(Vector2 posicion, int speed = -2);

    void Update();

    void Draw();
};