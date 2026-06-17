#pragma once
#include "grid.h"
#include "blocks.cpp"


class Game
{
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool gameOver;
    bool IsBlockOutside();
    bool BlockFits();
    void RotateBlock();
    void LockBlock();
    void Reset();

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

//ae :3 67