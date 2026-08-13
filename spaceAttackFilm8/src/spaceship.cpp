#include <raylib.h>
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
}

void Spaceship::Update()
{
    return;
}

void Spaceship::Draw()
{
    DrawTextureV(texture, posicion, WHITE);
}
