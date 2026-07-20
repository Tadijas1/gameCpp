#include <iostream>
#include <raylib.h>

#include "simulation.hpp"
using namespace std;

//zmienne globalne


int main()
{
    //zmienne lokalne
    Color grey = {29, 29, 29, 255};
    const int windowWigth = 750;
    const int windowHeight = 750;
    const int cellSize = 25;
    int FPS = 12;

    //TWORZENIE OKNA
    InitWindow(windowWigth, windowHeight, "lifeGame");
    
    //FPS
    SetTargetFPS(FPS);
    
    //TWORZENIE OBIEKTÓW
    Simulation simulation(windowWigth, windowHeight, cellSize);

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //1. Kolizie i akcje czasowe

        //2. Update obiektów i urządzenia wejścia
        //grid.Update();

        BeginDrawing();
        
            //3. Rysowanie następniej klatki
            ClearBackground(grey); 
            simulation.Draw();

        EndDrawing();
    }

    CloseWindow();
}