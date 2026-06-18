#pragma once
#include "colors.h"
#include "posicion.h"
#include <vector>
#include <map>

using namespace std;

class Block
{
    int cellSize;
    int pozycjaNum;
    int rowOffset, columnOffset;
    vector<Color> colors;
    
    public:
    int id;
    map<int, vector<Posicion>> pozycje;
    Block();
    void draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    void Rotation();
    void UndoRotation();
    vector<Posicion> GetCellPosicions();
};