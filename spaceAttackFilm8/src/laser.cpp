#include "laser.hpp"

Laser::Laser(Vector2 posicion, int speed)
{
    this -> posicion = posicion;
    this -> speed = speed;
    if(speed < 0) color = YELLOW;
    else color = {82, 32, 129, 255};
}

void Laser::Update()
{
    posicion.y += speed; 
}

void Laser::Draw()
{
    DrawRectangleV(posicion, {4, 15}, color);
}
