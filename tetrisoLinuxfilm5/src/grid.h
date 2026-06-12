#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

class Grid
{
    vector<Color> colors;
    int numRows;
    int numColu;
    int cellSize;

    public:
    Grid(int=20, int=10, int=30);
    void inicialize();
    void print();
    void draw();
    bool IsCellOutside(int row, int column);
    int grid[20][10];
};