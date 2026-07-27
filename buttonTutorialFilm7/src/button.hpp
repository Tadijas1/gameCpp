#pragma once
#include <raylib.h>

class Button
{
    Texture2D texture;
    Vector2 posicion;
    bool isClicked;

    public:
    Button(const char* imagePath, Vector2 imagePosicion, float scale);
    ~Button();

    bool isPressed(Vector2 mousePos, bool mousePressd);
    void Draw();
};