#include "button.hpp"

Button::Button(const char *imagePath, float scale)
{
    Image image = LoadImage(imagePath);
    
    int newWidth = static_cast<int>(image.width * scale);
    int newHeight = static_cast<int>(image.height * scale);
    
    ImageResize(&image, newWidth, newHeight);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    posicion = {0, 0};
    isClicked = false;
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::GetCenter(int windowWigth, int windowHeight, int heightOffset)
{
    int withCenter = windowWigth/2 - texture.width/2;
    int heightPosicion = (windowHeight - texture.height)/2 + heightOffset;
    posicion = (Vector2){withCenter, heightPosicion};
}

bool Button::isPressed(Vector2 mousePos, bool mousePressd)
{
    Rectangle rect = {posicion.x, posicion.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};

    if(CheckCollisionPointRec(mousePos, rect) && mousePressd) return true;
    return false;
}

void Button::Draw()
{
    DrawTextureV(texture, posicion, WHITE);
}
