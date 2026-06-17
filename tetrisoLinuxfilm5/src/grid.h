#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

class Grid
{
    bool IsRowFull(int row);
    void KillRow(int row);
    void MoveRowDown(int row, int howMany);
    vector<Color> colors;
    int numRows;
    int numColu;
    int cellSize;

    public:
    int grid[20][10];
    Grid(int=20, int=10, int=30);
    int ClearAllFullRows();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    void inicialize();
    void print();
    void draw();
};