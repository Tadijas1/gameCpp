#include "game.hpp"

void Game::Input()
{
    if(IsKeyDown(KEY_A)) spaceship.Move(-2.5);
    if(IsKeyDown(KEY_D)) spaceship.Move(2.5);
    if(IsKeyPressed(KEY_SPACE)) spaceship.FireLaser();
}

void Game::UpdateAll()
{
    for(int i = 0; i < spaceship.lasers.size(); i++) {
        spaceship.lasers[i].Update();
        if(spaceship.lasers[i].IsOutOffWindow()) spaceship.lasers.erase(spaceship.lasers.begin() + i);
    }
}
void Game::DrawAll()
{
    spaceship.Draw();
    for(auto& laser: spaceship.lasers) laser.Draw();
}
