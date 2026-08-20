#include <iostream>
#include "game.hpp"

void Game::KillingLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) { if(it -> IsOutOffWindow()) it = spaceship.lasers.erase(it); else it++; }
}
void Game::Input()
{
    if(IsKeyDown(KEY_A)) spaceship.Move(-2.5);
    if(IsKeyDown(KEY_D)) spaceship.Move(2.5);
    if(IsKeyPressed(KEY_SPACE)) spaceship.FireLaser();
}

void Game::UpdateAll()
{
    for(auto& laser: spaceship.lasers) laser.Update();
    KillingLasers();
}
void Game::DrawAll()
{
    spaceship.Draw();
    for(auto& laser: spaceship.lasers) laser.Draw();
}
