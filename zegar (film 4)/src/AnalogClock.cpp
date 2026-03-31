#include "AnalogClock.hpp"

using namespace std;

Color DARK_GREY = {45, 45, 45, 255};
Color LIGHT_GREY = {229, 229, 229, 255};

void AnalogClock::Update()
{
    time_t t = time(0);
    tm* now = localtime(&t);

    hour = now -> tm_hour % 12;
    minute = now -> tm_min;
    second = now -> tm_sec;
}

void AnalogClock::Draw() const
{
    DrawFace();
    DrawHourMarks();
    DrawSecondHand(second);
    DrawHourHand(hour, minute);
    DrawMinuteHand(minute);
    DrawCircleV(posicion, 15, DARKGRAY);
}

void AnalogClock::DrawFace() const
{
    DrawCircleV(posicion, size, DARK_GREY);
    DrawCircleV(posicion, size - 30, LIGHT_GREY);
    DrawCircleV(posicion, size - 40, RAYWHITE);
}

void AnalogClock::DrawHourMarks() const
{
    float rectWidth = 10;
    float rectHeight = size;

    Rectangle rect = Rectangle{posicion.x, posicion.y, rectWidth, rectHeight};
    for (int i = 0; i < 360; i += 30) DrawRectanglePro(rect, {rectWidth/2, rectHeight}, i, DARK_GREY);
    DrawCircleV(posicion, size - 50, RAYWHITE);
}

void AnalogClock::DrawSecondHand(int second) const
{
    float handWidth = 5;
    float handLenght = size * 1.05;
    int angle = second * 6;

    DrawHand(handWidth, handLenght, angle, RED, 55);
}

void AnalogClock::DrawMinuteHand(int minute) const
{
    float handWidth = 10;
    float handLenght = size * 0.7;
    int angle = minute * 6;

    DrawHand(handWidth, handLenght, angle, DARK_GREY, 0);
}

void AnalogClock::DrawHourHand(int hour, int minute) const
{
    float handWidth = 15;
    float handLenght = size * 0.6;
    int angle = hour * 30 + minute/2;

    DrawHand(handWidth, handLenght, angle, DARK_GREY, 0);
}

void AnalogClock::DrawHand(float handWidth, float handLength, int angle, Color color, int offset) const
{
    Rectangle handRect = Rectangle{posicion.x, posicion.y, handWidth, handLength};

    DrawRectanglePro(handRect, {handWidth/2, handLength - offset}, angle, color);
}