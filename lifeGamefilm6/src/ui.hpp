#pragma once
#include <raylib.h>
#include <string>

class Ui
{
    std::string modes[2] = {"normal", "battle"};
    int mode;
    int FPS;
    int TextSize;

    public:
    Ui(int mode, int FPS, int TextSize)
    : mode(1), FPS(0), TextSize(30) {};

    void ChangeMode() {mode++; if(mode == 3) mode = 1;};
    void Update() {FPS = GetFPS();}
    void Draw();
};