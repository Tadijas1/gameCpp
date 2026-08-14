#include <iostream>
#include <raylib.h>

#include "game.hpp"

//test lazygit :3

using namespace std;

int main()
{
    //zmienne lokalne
    const int windowWigth = 800;
    const int windowHeight = 600;
    int FPS = 60;
    
    //TWORZENIE OKNA
    InitWindow(windowWigth, windowHeight, "spaceAttack");
    
    //FPS
    SetTargetFPS(FPS);

    //TWORZENIE OBIEKTÓW
    Game game = Game();
    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //1. Kolizie i akcje czasowe
        game.Input();

        //2. Update obiektów i urządzenia wejścia
        game.UpdateAll();

        //3. Rysowanie następniej klatki
        BeginDrawing();
            ClearBackground(GRAY);
            game.DrawAll();
        EndDrawing();
    }

    CloseWindow();
}