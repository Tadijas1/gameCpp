#include <iostream>
#include <vector>
#include <utility>
#include <raylib.h>

#include "simulation.hpp"

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> nieghborsOffsets = 
    {
        {-1, 0}, // nad
        {1, 0}, // pod
        {0, -1}, // po lewej
        {0, 1}, // po prawej
        {-1, -1}, // lewa góra
        {-1, 1}, // prawa góra
        {1, -1}, // lewy dół
        {1, 1} // prawy dół
    };

    for (const auto& offset : nieghborsOffsets)
    {
        int neighborRow = (row + offset.first + grid.getRows()) % grid.getRows();
        int neighborColumn = (column + offset.second + grid.getColumns()) % grid.getColumns();
        liveNeighbors += grid.getValue(neighborRow, neighborColumn);
    }
    return liveNeighbors;
}

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::Input(int &FPS, int cellSize)
{
    int key = GetKeyPressed();

    switch (key)
    {
    case KEY_SPACE:
        Pause_Unpouse();
        if(running) SetWindowTitle("game of life RUNNING");
        else SetWindowTitle("game of life STOPPED");
        break;
    case KEY_F:
        FPS += 2;
        break;
    case KEY_S:
        if(FPS > 4) FPS -= 2;
        break;
    case KEY_R:
        if(!running) grid.FillRandomValue();
        break;
    case KEY_C:
        if(!running) grid.ClearGrid();
        break;
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (!running)) {
        Vector2 mousePosicion = GetMousePosition();
        int row = mousePosicion.y / cellSize;
        int column = mousePosicion.x / cellSize;

        grid.ChangeValue(row, column);
    }
}

void Simulation::Update()
{
    if(running) {
        for (int row = 0; row < grid.getRows(); row++) for (int column = 0; column < grid.getColumns(); column++)
        {
            int liveNeighbors = CountLiveNeighbors(row, column);
            int cellValue = grid.getValue(row, column);

            if(cellValue == 1) {
                if(liveNeighbors > 3 || liveNeighbors < 2) gridCopy.SetValue(row, column, 0);
                else gridCopy.SetValue(row, column, 1);
            }
            else {
                if(liveNeighbors == 3) gridCopy.SetValue(row, column, 1);
                else gridCopy.SetValue(row, column, 0);
            }
        }

        grid = gridCopy;
    }
}
