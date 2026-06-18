#pragma once
#include "grid.h"
#include "blocks.cpp"


class Game
{
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    vector<Block> blocks;
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
    bool IsBlockOutside();
    bool BlockFits();
    void RotateBlock();
    void LockBlock();
    void Reset();
    void MoveBlockLeft();
    void MoveBlockRight();
    
    public:
    Game();
    ~Game();
    Music music;
    int score;
    bool gameOver;
    bool wait;
    void Draw();
    void UpdateScore(int linesCleared, int moveDownPoints);
    void HandleInput();
    void MoveBlockDown();
};

//ae :3 67