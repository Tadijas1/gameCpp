#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
    vector<Color> GetCellColors();
    vector<Color> colors;
    int numRows;
    int numColu;
    int cellSize;

    public:
    Grid(int=20, int=10, int=30);
    void inicialize();
    void print();
    int grid[20][10];
};