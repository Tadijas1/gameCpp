#include "grid.h"
#include "colors.h"
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

void Grid::draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numColu; column++)
        {
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize+1, row * cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
        }  
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if(row >= 0 && row < numRows && column >= 0 && column < numColu) return false;
    else return true;
}