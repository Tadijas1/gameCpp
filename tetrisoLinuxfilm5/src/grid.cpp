#include "grid.h"
#include <iostream>
#include <vector>
#include <raylib.h>

using namespace std;

Grid::Grid(int nR, int nC, int cS)
{
    numRows = nR;
    numColu = nC;
    cellSize = cS;
    inicialize();
    colors = GetCellColors();
}

void Grid::inicialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numColu; column++)
        {
            grid[row][column] = 0;
        }  
    }
    
}

void Grid::print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numColu; column++)
        {
            cout<<grid[row][column]<<" ";
        }
        cout<<endl;
    }
}

vector<Color> Grid::GetCellColors()
{    
    Color darkGrey = {26, 31, 40, 255};
    Color green = {47, 230, 23, 255};
    Color red = {232, 18, 18, 255};
    Color orange = {226, 116, 17, 255};
    Color yellow = {237, 234, 4, 255};
    Color purple = {166, 0, 247, 255};
    Color cyan = {21, 204, 209, 255};
    Color blue = {13, 63, 216, 255};

    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}

////////////////////////////////////////////////////////////////