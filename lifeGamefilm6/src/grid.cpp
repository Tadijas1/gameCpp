#include <raylib.h>

#include "grid.hpp"

void Grid::Draw()
{
    for(int column = 0; column < columns; column++) for(int row = 0; row < rows; row++)
    {
        Color color;
        if(alive) color = GREEN;
        else color = BLACK;
    }
}
