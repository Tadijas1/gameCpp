#include "grid.h"
#include "colors.h"
#include <iostream>
#include <vector>
#include <raylib.h>

using namespace std;

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < numColu; column++) if(grid[row][column] == 0) return false;
    return true;
}

void Grid::KillRow(int row) {for (int column = 0; column < numColu; column++) grid[row][column] = 0;}

void Grid::MoveRowDown(int row, int howMany)
{
    for (int column = 0; column < numColu; column++)
    {
        grid[row + howMany][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

Grid::Grid(int nR, int nC, int cS)
{
    numRows = nR;
    numColu = nC;
    cellSize = cS;
    inicialize(); 
    colors = GetCellColors();
}

int Grid::ClearAllFullRows()
{
    int howManyFull = 0;
    for (int row = numRows-1; row >= 0; row--)
    {
        if(IsRowFull(row)) {
            KillRow(row);
            howManyFull++;
        }
        else if(howManyFull>0) MoveRowDown(row, howManyFull);
    }
    return howManyFull;
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
            DrawRectangle(column * cellSize+11, row * cellSize+11, cellSize-1, cellSize-1, colors[cellValue]);
        }  
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if(row >= 0 && row < numRows && column >= 0 && column < numColu) return false;
    else return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if(grid[row][column] == 0) return true;
    return false;
}
