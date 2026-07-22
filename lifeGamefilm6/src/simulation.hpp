#pragma once

#include "grid.hpp"
#include "ui.hpp"

class Simulation
{
    Grid grid;
    Grid gridCopy;
    Ui ui;
    bool running;

    public:
    Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize), gridCopy(width, height, cellSize), running(false), ui(1, GetFPS(), 30) {};
    
    int CountLiveNeighbors(int row, int column);
    void SetCellValue(int row, int column, int value);
    void Pause_Unpouse() {running = !running;}
    void Input(int &FPS, int cellSize);
    void Update();
    void Draw();
};
