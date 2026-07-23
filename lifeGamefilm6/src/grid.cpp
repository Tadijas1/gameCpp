#include <raylib.h>
#include <random>

#include "grid.hpp"

bool Grid::IsWithinBounds(int row, int column)
{
    if(row >= 0 && row < rows && column >= 0 && column < columns) return true;
    else return false;
}

void Grid::ChangeValue(int row, int column, int value)
{
    if(IsWithinBounds(row, column)) cells[row][column] = value;
}

void Grid::ClearGrid()
{
    for (int row = 0; row < rows; row++) for (int column = 0; column < columns; column++)
    {
        cells[row][column] = 0;
    }
}

void Grid::SetValue(int row, int column, int value)
{
    if(IsWithinBounds(row, column)) cells[row][column] = value;
}

int Grid::getValue(int row, int column)
{
    if(IsWithinBounds(row, column)) return cells[row][column];
    else return 0;
}

void Grid::FillRandomValue(int mode)
{
    for (int row = 0; row < rows; row++) for (int column = 0; column < columns; column++)
    {
        if(mode == 2 && column > columns/2) {
            cells[row][column] = (GetRandomValue(0, 4) == 4) ? 2 : 0;
        }
        else cells[row][column] = (GetRandomValue(0, 4) == 4) ? 1 : 0;
    }
}

void Grid::Draw()
{
    for(int column = 0; column < columns; column++) for(int row = 0; row < rows; row++)
    {
        //komórka == 1 to color = zielony, w przeciwnym razie color = szary
        Color color;
        if(cells[row][column] == 2) color = PURPLE; 
        else if(cells[row][column] == 1) color = {0, 255, 0, 255};
        else color = {55, 55, 55, 255};
        DrawRectangle(column * cellSize, row * cellSize, cellSize-1, cellSize-1, color);
    }
}
