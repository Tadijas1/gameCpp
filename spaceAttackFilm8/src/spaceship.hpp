#pragma once
#include <raylib.h>

class Spaceship
{
    Texture2D texture;
    Vector2 posicion;

    public:
    Spaceship();
    ~Spaceship();

    void Move(float speed);
    void FireLaser();

    void Update();
    void Draw();
};