#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "score.h"
#include <string>

using namespace std;

class Game
{
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    vector<Score> GetScores();

    vector<Block> blocks;
    vector<Score> scores;
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    Music chempions;
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
    Music orginal;
    Music tripoloski;
    Music gameOverMusic;
    int player_score;
    float BlockSpeed;
    double gameOverTime;
    bool canReset;
    bool music_change;
    bool gameOver;
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