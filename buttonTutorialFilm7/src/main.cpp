#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "button.hpp"

using namespace std;

int main()
{
    //zmienne lokalne
    const int windowWigth = 800;
    const int windowHeight = 600;
    int FPS = 60;
    bool exit = false;
    
    //TWORZENIE OKNA
    InitWindow(windowWigth, windowHeight, "button_tutorial");
    
    //obraz w tle
    Texture2D background = LoadTexture("pictures/background.png");
    float scale = static_cast<float>(windowHeight)/ background.height;


    //FPS
    SetTargetFPS(FPS);

    //TWORZENIE OBIEKTÓW
    Button startButton = Button("pictures/button_start.png", 0.5); startButton.GetCenter(windowWigth, windowHeight, -100);
    Button exitButton = Button("pictures/button_exit.png", 0.5); exitButton.GetCenter(windowWigth, windowHeight, 100);

    //PĘTLA GRY
    while(WindowShouldClose() == false && exit == false)
    {
        //1. Kolizie i akcje czasowe
        
        
        //2. Update obiektów i urządzenia wejścia
        if(startButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) cout<<"starging game"<<endl;
        if(exitButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) exit = true;

        //3. Rysowanie następniej klatki
        BeginDrawing();
            ClearBackground(GREEN);
            DrawTextureEx(background, (Vector2){0, 0}, 0.0f, scale ,WHITE);
            startButton.Draw();
            exitButton.Draw();
        EndDrawing();
    }

    UnloadTexture(background);

    CloseWindow();
}