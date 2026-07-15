#include <iostream>
#include <raylib.h>

#include "game.hpp"

using namespace std;

//zmienne globalne


int main()
{
    //zmienne lokalne
    Color grey = {29, 29, 29, 255};
    const int windowWigth = 750;
    const int windowHeight = 750;
    int FPS = 12;

    //TWORZENIE OKNA
    InitWindow(windowWigth, windowHeight, "lifeGame");
    
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
        game.Update();

        BeginDrawing();
        
            //3. Rysowanie następniej klatki
            ClearBackground(grey);
            game.Draw(); 

        EndDrawing();
    }

    CloseWindow();
}