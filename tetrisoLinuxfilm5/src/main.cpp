#include "game.hpp"
#include "colors.h"
#include <iostream>
#include <raylib.h>

using namespace std;

//zmienne globalne
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
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    //TWORZENIE OBIEKTÓW
    Game game = Game ();

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
		UpdateMusicStream(game.music);
        //1. Update obiektów i urządzenia wejścia
        game.HandleInput();
        //2. Kolizie i akcje czasowe
        if (EventTriggered(0.3)) game.MoveBlockDown();

        //3. Rysowanie następniej klatki
        BeginDrawing();
        ClearBackground(darkBlue);

        //drawing decoration elements
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
        
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        
        if(game.gameOver) DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        
        //drawing grid and blocks
        game.Draw();
        EndDrawing();
        if(game.gameOver && game.wait) {WaitTime(2); game.wait=false;}
    }

    CloseWindow();
}