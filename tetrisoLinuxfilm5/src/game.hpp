#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <string>

using namespace std;

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
    void SaveScore();
    void MoveBlockLeft();
    void MoveBlockRight();
    
    public:
    Game();
    ~Game();
    Music music;
    int score;
    bool gameOver;
    bool wait;
    bool game_started;
    string playerName;
    void ShowLiderboard();
    void Draw();
    void UpdateScore(int linesCleared, int moveDownPoints);
    void HandleInput();
    void MoveBlockDown();
    void InitNicname();
};

//ae :3 67