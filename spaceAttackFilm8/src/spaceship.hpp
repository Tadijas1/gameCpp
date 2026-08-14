#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"

class Spaceship
{
    Texture2D texture;
    Vector2 posicion;

    public:
    std::vector<Laser> lasers;

    Spaceship();
    ~Spaceship();

    void Move(float speed);
    void FireLaser();

    void Update();
    void Draw();
};