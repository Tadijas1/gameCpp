#include <iostream>
#include <raylib.h>

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

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //1. Kolizie i akcje czasowe
        
        //2. Update obiektów i urządzenia wejścia

        //3. Rysowanie następniej klatki
        BeginDrawing();
            ClearBackground(GREEN);

        EndDrawing();
    }

    CloseWindow();
}