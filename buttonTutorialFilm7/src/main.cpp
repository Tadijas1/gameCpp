#include <iostream>
#include <raylib.h>

#include "button.hpp"

using namespace std;

int main()
{
    //zmienne lokalne
    const int windowWigth = 800;
    const int windowHeight = 600; 
    int FPS = 60;

    
    //TWORZENIE OKNA
    InitWindow(windowWigth, windowHeight, "button_tutorial");
    
    //obraz w tle
    Texture2D background = LoadTexture("pictures/background.png");

    //FPS
    SetTargetFPS(FPS);

    //TWORZENIE OBIEKTÓW
    Button startButton = Button("pictures/button_start.png", {210,20}, 0.5);
    Button exitButton = Button("pictures/button_exit.png", {210,320}, 0.5);

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //1. Kolizie i akcje czasowe
        
        
        //2. Update obiektów i urządzenia wejścia
        if(startButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) cout<<"starging game"<<endl;
        if(exitButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) CloseWindow();

        //3. Rysowanie następniej klatki
        BeginDrawing();
            ClearBackground(GREEN);
            DrawTexture(background, 0, 0, WHITE);
            startButton.Draw();
            exitButton.Draw();
        EndDrawing();
    }

    CloseWindow();
}