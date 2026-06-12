#pragma once
#include "grid.h"
#include "blocks.cpp"


class Game
{
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();

    public:
    Game();
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    Grid grid;
};