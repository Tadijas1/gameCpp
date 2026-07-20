#include <vector>
#include <utility>
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

void Simulation::Update()
{
    
}
