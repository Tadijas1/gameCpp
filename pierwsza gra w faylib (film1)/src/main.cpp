#include <raylib.h>

int main()
{
    //Deklarowanie zmiennych
    int ballX = 400; int ballY = 400;
    Color green = {20, 160, 133, 255};

    //Tworzenie okienka
    InitWindow(800, 800, "Moja pierwsza gra w raylib");
    // Liczba klatek
    SetTargetFPS(60);

    //Pętla gry
    while(WindowShouldClose() == false)
    {
        //1. Co wprowadzono z klawiatury, myszki etc.

        if(IsKeyDown(KEY_RIGHT)) ballX += 2;
        else if(IsKeyDown(KEY_LEFT)) ballX -= 2;
        if(IsKeyDown(KEY_DOWN)) ballY += 2;
        else if(IsKeyDown(KEY_UP)) ballY -= 2;

        //2. Update pozycji

        //3. Rysowanie następnej klatki
        BeginDrawing();
        ClearBackground(green);
        DrawCircle(ballX, ballY, 30, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}