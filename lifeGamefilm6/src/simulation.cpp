#include <iostream>
#include <vector>
#include <utility>
#include <raylib.h>

#include "simulation.hpp"

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

void Simulation::ChangeMode()
{
    mode++;
    if(mode == 3) {
        mode = 1;
        ClearOtherColors();
    }
}

void Simulation::ClearOtherColors()
{
    for (int row = 0; row < grid.getRows(); row++) for (int column = 0; column < grid.getColumns(); column++)
    {
        if(grid.getValue(row, column) == 2) SetCellValue(row, column, 0);
    }
}

std::vector<int> Simulation::CountLiveNeighbors(int row, int column)
{
    std::vector<int> liveNeighbors(allmodes);

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

        if(grid.getValue(row, column) != 0)
        {
            if(grid.getValue(row, column) == grid.getValue(neighborRow, neighborColumn)){
                liveNeighbors[grid.getValue(row, column)-1]++;
            }
        } else {
            if(grid.getValue(neighborRow, neighborColumn) != 0) liveNeighbors[grid.getValue(neighborRow, neighborColumn)-1]++;
        }
    }
    return liveNeighbors;
}

void Simulation::Draw(int FPS)
{
    grid.Draw();
    ui.Draw(FPS, mode);
}

void Simulation::Input(int &FPS, int cellSize)
{
    int key = GetKeyPressed();

    //keybord input
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
        if(!running) grid.FillRandomValue(mode);
        break;
    case KEY_C:
        if(!running) grid.ClearGrid();
        break;
    case KEY_M:
        ChangeMode();
        break;
    }

    //mouse input
    if(!running) {
        Vector2 mousePosicion = GetMousePosition();
        int row = mousePosicion.y / cellSize;
        int column = mousePosicion.x / cellSize;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if(grid.getValue(row, column) != 1) grid.ChangeValue(row, column, 1);
            else grid.ChangeValue(row, column, 0);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && mode == 2) {
            if(grid.getValue(row, column) != 2) grid.ChangeValue(row, column, 2);
            else grid.ChangeValue(row, column, 0);
        }
    }
}

void Simulation::Update()
{
    if(running) {
        for (int row = 0; row < grid.getRows(); row++) for (int column = 0; column < grid.getColumns(); column++)
        {
            std::vector<int> liveNeighbors = CountLiveNeighbors(row, column);
            int cellValue = grid.getValue(row, column);

            if(cellValue != 0) {
                if(liveNeighbors[cellValue-1] > 3 || liveNeighbors[cellValue-1] < 2) gridCopy.SetValue(row, column, 0);
                else gridCopy.SetValue(row, column, cellValue);
            }
            else {
                bool neighbors3 = false;
                for(int i = 0; i < allmodes; i++) {
                    if(liveNeighbors[i] == 3) {gridCopy.SetValue(row, column, i+1); neighbors3 = true;}
                }
                if(!neighbors3) gridCopy.SetValue(row, column, 0);
            }
        }

        grid = gridCopy;
    }
}
