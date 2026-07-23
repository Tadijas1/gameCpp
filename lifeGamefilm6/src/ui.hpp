#pragma once
#include <raylib.h>
#include <string>

class Ui
{
    std::string modes[2] = {"normal", "battle"};
    int TextSize;

    public:
    Ui(int TextSize)
    : TextSize(30) {};

    void Draw(int FPS, int mode);
};