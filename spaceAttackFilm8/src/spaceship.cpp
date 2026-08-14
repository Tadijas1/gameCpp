#include <raylib.h>
#include <iostream>
#include "spaceship.hpp"

Spaceship::Spaceship()
{
    texture = LoadTexture("pictures/spaceship.png");

    posicion = {(GetScreenWidth() - texture.width)/2.0f, GetScreenHeight() - texture.height - 10.0f};
}

Spaceship::~Spaceship()
{
    UnloadTexture(texture);
}

void Spaceship::Move(float speed)
{
    posicion.x += speed;

    if(posicion.x > GetScreenWidth() - texture.width) posicion.x = GetScreenWidth() - texture.width;
    else if(posicion.x < 0)posicion.x = 0;

    lastFireTime = 0;
}

void Spaceship::FireLaser()
{
    if(GetTime() - lastFireTime >+ 0.35) {
        lasers.push_back(Laser({posicion.x + texture.width/2 - 2, posicion.y - 10}));
        lastFireTime = GetTime();
    }
}

void Spaceship::Draw()
{
    DrawTextureV(texture, posicion, WHITE);
}
