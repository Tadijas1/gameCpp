#pragma once
#include <raylib.h>
#include "spaceship.hpp"

class Game
{
    Spaceship spaceship;

    public:
    Game() {};
    ~Game() {};

    void Input();
    void UpdateAll();
    void DrawAll();
};