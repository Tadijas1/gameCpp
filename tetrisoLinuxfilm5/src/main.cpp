#include "game.hpp"
#include "colors.h"
#include <iostream>
#include <raylib.h>
#include <cstring>

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
    if(strcmp(text, "QUIT") == 0) fontSize = 18;
    int textWidth = MeasureText(text, fontSize);

    if(strcmp(text, "QUIT") == 0) DrawTextEx(GetFontDefault(), text, {rect.x + rect.width/2 - textWidth/2 - 4, rect.y + rect.height / 2 - fontSize / 2}, fontSize, 4, WHITE);
    else DrawText(text, rect.x + rect.width/2 - textWidth/2, rect.y + rect.height / 2 - fontSize / 2, fontSize, WHITE);
    return clicked;
}

int main()
{
    //TWORZENIE OKNA
    InitWindow(500, 620, "Tetris");

    //Inportowanie czcionki
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    //Dodawanie obrazka do menu
    Texture2D background = LoadTexture("pic/background.png");
    Rectangle source = {0, 0, (float)background.width, (float)background.height};
    Rectangle dest = {0, 0, (float)background.width, (float)background.height};
    Texture2D music_icon = LoadTexture("pic/music_icon.png");
    
    //FPS
    SetTargetFPS(60);
    
    
    //TWORZENIE OBIEKTÓW
    Game game = Game ();
    
    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //Muzyka
		if(game.music_change && !game.gameOver) UpdateMusicStream(game.orginal);
        else if(!game.music_change && !game.gameOver) UpdateMusicStream(game.tripoloski);
        
        if(game.game_started) {
            //1. Kolizie i akcje czasowe
            if (EventTriggered(game.BlockSpeed)) game.MoveBlockDown();

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
            sprintf(scoreText, "%d", game.player_score);
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

            //music change button
            Color button_color;
            if(game.music_change) button_color = BLUE;
            else button_color = RED;
            DrawRectangleRec(Rectangle{465, 10, 25, 25}, button_color);
            DrawTexturePro(music_icon, source, {467, 13, 20, 20}, {0, 0}, 0.0f, WHITE);
            if(buttonClicked({465, 10, 25, 25}, "")) {
                if(game.music_change) game.music_change = false;
                else game.music_change = true;
            }

            //quit button
            DrawRectangleRec(Rectangle{10, 10, 70, 25}, darkRed);
            if(buttonClicked({10, 10, 70, 25}, "QUIT")) {
                UnloadTexture(background);
                UnloadTexture(music_icon);
                CloseWindow();
                return 0;
            }
        }
        EndDrawing();

        //Jak gra się zakończyła to czekać
        if(game.gameOver) {
            //Music
            UpdateMusicStream(game.gameOverMusic);
            if (GetTime() - game.gameOverTime >= 6.5) {
                
                game.canReset = true;
                game.HandleInput();
            }
        }
    }
    CloseWindow();
}