#include "game.hpp"

void Game::Input()
{
    if(IsKeyDown(KEY_A)) spaceship.Move(-2.5);
    if(IsKeyDown(KEY_D)) spaceship.Move(2.5);
    if(IsKeyPressed(KEY_SPACE)) spaceship.FireLaser();
}

void Game::UpdateAll()
{
    spaceship.Update();
}

void Game::DrawAll()
{
    spaceship.Draw();
}
