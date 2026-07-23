#include <iostream>
#include <raylib.h>

#include "simulation.hpp"

using namespace std;

int main()
{
    //zmienne lokalne
    Color grey = {29, 29, 29, 255};
    const int windowWigth = 1000;
    const int windowHeight = 800;
    const int cellSize = 20;
    int FPS = 12;

    //TWORZENIE OKNA
    InitWindow(windowWigth, windowHeight, "game of life STOPPED");
    
    //TWORZENIE OBIEKTÓW
    Simulation simulation(windowWigth, windowHeight, cellSize);


    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //1. Kolizie i akcje czasowe
        simulation.Input(FPS, cellSize);
        
        //FPS
        SetTargetFPS(FPS);
        
        //2. Update obiektów i urządzenia wejścia
        simulation.Update();

        BeginDrawing();
        
            //3. Rysowanie następniej klatki
            ClearBackground(grey); 
            simulation.Draw(FPS);
        EndDrawing();
    }

    CloseWindow();
}