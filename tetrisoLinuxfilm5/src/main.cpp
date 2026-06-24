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

bool buttonClicked(Rectangle rect, const char* text)
{
    Vector2 mousePos = GetMousePosition();

    bool clicked = CheckCollisionPointRec(mousePos, rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(text, rect.x + rect.width/2 - textWidth/2, rect.y + rect.height / 2 - fontSize / 2, fontSize, WHITE);
    return clicked;
}

int main()
{
    //TWORZENIE OKNA
    InitWindow(500, 620, "Tetris");

    //Dodawanie obrazka do menu
    Texture2D background = LoadTexture("pic/v2.png");
    Rectangle source = {0, 0, (float)background.width, (float)background.height};
    Rectangle dest = {0, 0, (float)background.width, (float)background.height};
    
    //FPS
    SetTargetFPS(60);
    
    //Inportowanie czcionki
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    
    //TWORZENIE OBIEKTÓW
    Game game = Game ();
    
    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //Muzyka
		UpdateMusicStream(game.music);
        
        
        if(game.game_started) {
            //1. Kolizie i akcje czasowe
            if (EventTriggered(0.3)) game.MoveBlockDown();

            //2. Update obiektów i urządzenia wejścia
            game.HandleInput();
            
        }
        
        BeginDrawing();
        
        if(game.game_started) {
            //3. Rysowanie następniej klatki
            ClearBackground(darkBlue);
            
            //drawing decoration elements
            //Score
            DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
            
            //Next block
            DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
            
            //Game over text
            if(game.gameOver) DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
            
            //drawing grid and blocks
            game.Draw();
            
        } else {
            ClearBackground(BLACK);

            //Rysowanie menu
            DrawTexturePro(background, source, dest, {0,0}, 0.0f, WHITE);
            
            //start button
            DrawRectangleRec(Rectangle{190, 230, 129, 40}, BLUE);
            if(buttonClicked({190, 230, 129, 40}, "start")) {game.InitNicname(); game.game_started = true;}
                
            //liderboard button
            DrawRectangleRec(Rectangle{190, 295, 129, 40}, BLUE);
            if(buttonClicked({190, 295, 129, 40}, "liderboard")) game.ShowLiderboard();
        }
        EndDrawing();

        //Jak gra się zakończyła to czekać
        if(game.gameOver && game.wait) {WaitTime(2); game.wait=false;}
    }
    
    UnloadTexture(background);
    CloseWindow();
}