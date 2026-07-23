#pragma once
#include <vector>

#include "grid.hpp"
#include "ui.hpp"

class Simulation
{
    Grid grid;
    Grid gridCopy;
    Ui ui;
    bool running;
    int allmodes;
    int mode;

    public:
    Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize), gridCopy(width, height, cellSize), running(false), ui(30), allmodes(2) ,mode(1) {};
    
    void ChangeMode();
    void ClearOtherColors();
    
    std::vector<int> CountLiveNeighbors(int row, int column);
    void SetCellValue(int row, int column, int value);
    void Pause_Unpouse() {running = !running;}
    void Input(int &FPS, int cellSize);
    void Update();
    void Draw(int FPS);
};
