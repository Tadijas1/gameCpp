#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 posicion, int speed)
{
    this -> posicion = posicion;
    this -> speed = speed;
    if(speed < 0) color = YELLOW;
    else color = {82, 32, 129, 255};
}

bool Laser::IsOutOffWindow()
{
    if(posicion.y > GetScreenHeight() + 15 || posicion.y < 0) return true;
    else return false;
}

void Laser::Update()
{
    posicion.y += speed;
}

void Laser::Draw()
{
    DrawRectangleV(posicion, {4, 15}, color);
}
