#pragma once
#include <raylib.h>
#include <ctime>

class AnalogClock {
    private:
    int size;
    Vector2 posicion;
    int hour;
    int minute;
    int second;

    public:
    AnalogClock(int size, Vector2 posicion) :size(size), posicion(posicion), hour(0), minute(0), second(0) {};
    void Update();
    void Draw() const;
    void DrawFace() const;
    void DrawHourMarks() const;
    void DrawMinuteHand(int minute) const;
    void DrawHourHand(int hour, int minute) const;
    void DrawSecondHand(int second) const;
    void DrawHand(float handWidth, float handLength, int angle, Color color, int offset) const;
};