#pragma once
#include <raylib.h>

class AnalogClock {
    private:
    int size;
    Vector2 posicion;

    public:
    AnalogClock(int size, Vector2 posicion) :size(size), posicion(posicion) {};
    void Draw() const;
    void DrawFace() const;
};