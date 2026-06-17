#include "game.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

//zmienne globalne
Color darkBlue = {44, 44, 127, 255};
double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    //TWORZENIE OKNA
    InitWindow(500, 620, "Tetris");

    //FPS
    SetTargetFPS(60);

    //Inportowanie czcionki
    Font font = LoadFontEx("../Font/monogram.ttf", 64, 0, 0);

    //TWORZENIE OBIEKTÓW
    Game game = Game ();
    
    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
		
        //1. Update obiektów i urządzenia wejścia
        game.HandleInput();
        //2. Kolizie i akcje czasowe
        if (EventTriggered(0.3)) game.MoveBlockDown();

        //3. Rysowanie następniej klatki
        BeginDrawing();
        ClearBackground(darkBlue);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}