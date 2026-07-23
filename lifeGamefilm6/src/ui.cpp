#include <raylib.h>

#include "ui.hpp"

void Ui::Draw(int FPS)
{
    //rysowanie licznika fps
    int textWidth = MeasureText(TextFormat("%i", FPS), TextSize);

    DrawText(TextFormat("%i", FPS), GetScreenWidth() - textWidth - 15, 15, TextSize, RED);

    //rysowanie napisu z trybem
    std::string text;
    if(mode == 1) text = modes[0];
    else if(mode == 2) text = modes[1];

    textWidth = MeasureText(text.c_str(), TextSize);

    DrawText(text.c_str(), GetScreenWidth()/2 - textWidth/2, GetScreenHeight() - 45, TextSize,  WHITE);
}