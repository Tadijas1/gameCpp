#include <iostream>
#include <raylib.h>
#include "AnalogClock.hpp"

using namespace std;

//zmienne globalne

int main()
{

    //zmienne lokalne
    Color BEŻOWY = {255, 239, 240, 255};

    //TWORZENIE OKNA
    const int WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib-Clock");

    //FPS
    SetTargetFPS(60);

    //TWORZENIE OBIEKTÓW 
    AnalogClock clock {250, {WINDOW_WIDTH/2, WINDOW_HEIGHT/2}};

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {

        //1. Wejście z klawiatury
        
        //2. Update obiektów
        clock.Update();
        
        //3. Rysowanie następniej klatki
        BeginDrawing();
        ClearBackground(BEŻOWY);

        clock.Draw();

        EndDrawing();
    }

    CloseWindow();
}