#pragma once

#include "grid.hpp"

class Simulation
{
    Grid grid;
    Grid gridCopy;

    public:
    Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize), gridCopy(width, height, cellSize) {};
    
    void SetCellValue(int row, int column, int value);
    int CountLiveNeighbors(int row, int column);
    void Draw();
    void Update();
};
