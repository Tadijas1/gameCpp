#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"

class Spaceship
{
    Texture2D texture;
    Vector2 posicion;
    double lastFireTime;

    public:
    std::vector<Laser> lasers;

    Spaceship();
    ~Spaceship();

    void Move(float speed);
    void FireLaser();

    void Draw();
};