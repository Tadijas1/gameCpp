#pragma once
#include <vector>

class Grid
{
    bool alive;
    int cellSize;
    int rows, columns;
    std::vector<std::vector<int>> cells;

    public:
    Grid(int width, int height, int cellSize)
    : rows(height/cellSize), columns(width/cellSize), cellSize(cellSize), cells(rows, std::vector<int>(columns, 0)) {};

    void Draw();
};