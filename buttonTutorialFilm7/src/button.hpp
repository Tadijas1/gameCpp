#pragma once
#include <raylib.h>

class Button
{
    Texture2D texture;
    Vector2 posicion;
    bool isClicked;

    public:
    Button(const char* imagePath, float scale);
    ~Button();

    void GetCenter(int windowWigth, int windowHeight, int heightOffset);
    bool isPressed(Vector2 mousePos, bool mousePressd);
    void Draw();
};