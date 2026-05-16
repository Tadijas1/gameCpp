#include <iostream>
#include <raylib.h>
#include "grid.h"

using namespace std;

//zmienne globalne
Color darkBlue = {44, 44, 127, 255};

 

int main()
{
    //TWORZENIE OKNA
    InitWindow(300, 600, "Tetris");

    //FPS
    SetTargetFPS(60);

    //TWORZENIE OBIEKTÓW
    Grid grid = Grid();
    grid.print();

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
		
        //1. Update obiektów i urządzenia wejścia
        
        //2. Kolizie

        //3. Rysowanie następniej klatki
        ClearBackground(darkBlue);

        EndDrawing();
    }

    CloseWindow();
}