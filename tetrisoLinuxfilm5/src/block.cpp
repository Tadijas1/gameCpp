#include "block.h"

Block::Block()
{
    cellSize = 30;
    pozycjaNum = 0;
    colors = GetCellColors(); 
    rowOffset = 0;
    columnOffset = 0;
}

void Block::draw()
{
    vector<Posicion> tiles = GetCellPosicions();
    for(Posicion item: tiles) DrawRectangle(item.column * cellSize + 11, item.row * cellSize + 11, cellSize - 1, cellSize - 1, colors[id]);
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

void Block::Rotation()
{
    pozycjaNum++;
    if(pozycjaNum == (int)pozycje.size()) pozycjaNum = 0;
}

void Block::UndoRotation()
{
    pozycjaNum--;
    if(pozycjaNum == -1) pozycjaNum = pozycje.size() - 1;
}

vector<Posicion> Block::GetCellPosicions()
{
    vector<Posicion> tiles = pozycje[pozycjaNum];   
    vector<Posicion> movedTiles;

    for(Posicion item: tiles) {
        Posicion newPos = Posicion(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}