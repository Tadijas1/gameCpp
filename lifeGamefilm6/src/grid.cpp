#include <raylib.h>

#include "grid.hpp"

bool Grid::IsWithinBounds(int row, int column)
{
    if(row >= 0 && row < rows && column >= 0 && column < columns) return true;
    else return false;
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

void Grid::Draw()
{
    for(int column = 0; column < columns; column++) for(int row = 0; row < rows; row++)
    {
        //komórka == 1 to color = zielony, w przeciwnym razie color = szary
        Color color = cells[row][column] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
        DrawRectangle(column * cellSize, row * cellSize, cellSize-1, cellSize-1, color);
    }
}
