#pragma once
#include <raylib.h>
#include <string>

class Ui
{
    std::string modes[2] = {"normal", "battle"};
    int mode;
    int TextSize;

    public:
    Ui(int mode, int TextSize)
    : mode(1), TextSize(30) {};

    void ChangeMode() {mode++; if(mode == 3) mode = 1;};
    void Draw(int FPS);
};