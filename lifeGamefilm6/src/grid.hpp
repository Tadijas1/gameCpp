#pragma once
#include <vector>

class Grid
{
    int cellSize;
    int rows, columns;
    std::vector<std::vector<int>> cells;

    public:
    Grid(int width, int height, int cell_size)
    : rows(height/cellSize), columns(width/cellSize), cellSize(cell_size), cells(rows, std::vector<int>(columns, 0)) {};

    bool IsWithinBounds(int row, int column);
    void SetValue(int row, int column, int value);
    int getValue(int row, int column);
    int getRows() {return rows;}
    int getColumns() {return columns;}
    void Draw();
};