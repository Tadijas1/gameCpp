#include "AnalogClock.hpp"

Color DARK_GREY = {45, 45, 45, 255};
Color LIGHT_GREY = {229, 229, 229, 255};

void AnalogClock::Draw() const
{
    DrawFace();
}

void AnalogClock::DrawFace() const
{
    DrawCircleV(posicion, size, DARK_GREY);
    DrawCircleV(posicion, size - 30, LIGHT_GREY);
    DrawCircleV(posicion, size - 40, RAYWHITE);
}
