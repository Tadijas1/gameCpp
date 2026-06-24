#include "game.hpp"
#include "colors.h"
#include <random>
#include <string>
#include <fstream>

using namespace std;

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    wait=false;
    game_started = false;
    playerName = "Unnown player";
    InitAudioDevice();
    //music = LoadMusicStream("Sounds/music.mp3");
    music = LoadMusicStream("Sounds/tripoloski.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}

void Game::InitNicname()
{
    string nicname;
    while (!IsKeyPressed(KEY_ENTER) && WindowShouldClose() == false)
    {
        ClearBackground(darkBlue);
        int key = GetCharPressed();
        
        while(key > 0)
        {
            if(key >= 32 && key<= 126) nicname += (char)key;
            key = GetCharPressed();
        }
        
        if(IsKeyPressed(KEY_BACKSPACE) && !nicname.empty()) nicname.pop_back();
        
        BeginDrawing();
        DrawText("Type your's nicmane: ", 10, 10, 30, WHITE);
        DrawText(nicname.c_str(), 15, 50, 30, WHITE);
        EndDrawing();
    }
    if(!nicname.empty()) playerName = nicname;
    return;
}

Block Game::GetRandomBlock()
{
    if(blocks.empty()) blocks = GetAllBlocks();
    
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::ShowLiderboard()
{
    string line;
    string Filescore;
    bool waiting = true;
    
    while(WindowShouldClose() == false && waiting)
    {
        ifstream scores("gamefiles/scores.txt");
        ClearBackground(darkBlue);
        int keyPressed = GetKeyPressed();
        int textPosY = 15;
        BeginDrawing();
        while (getline(scores, line) && getline(scores, Filescore))
        {
            string text = line+": "+Filescore;
            DrawText(text.c_str(), 10, textPosY, 20, WHITE);
            textPosY += 30;
        }
        DrawText("PRESS ANY KEY TO GO BACK...", 10, textPosY+20, 20, WHITE);
        EndDrawing();
        if(keyPressed != 0) waiting=false;
        scores.close();
    }
}

void Game::Draw()
{
    grid.draw();
    currentBlock.draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.draw(255, 290);
        break;
    case 4:
        nextBlock.draw(255, 280);
        break;
    default:
        nextBlock.draw(270, 270);
        break;
    }
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;    
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0){ gameOver = false; Reset(); game_started = false;}
    switch(keyPressed) {
        case KEY_LEFT:
        MoveBlockLeft();
        break;
        case KEY_RIGHT:
        MoveBlockRight();
        break;
        case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;
        case KEY_UP:
        RotateBlock();
        break;
    }
}

bool Game::IsBlockOutside()
{
    vector<Posicion> tiles = currentBlock.GetCellPosicions();
    for(Posicion item: tiles) {
        if(grid.IsCellOutside(item.row, item.column)) return true;
    }
    return false;
}

void Game::MoveBlockLeft()
{
    if(!gameOver) {
        currentBlock.Move(0, -1);
        if(IsBlockOutside() || BlockFits() == false) currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight()
{
    if(!gameOver) {
        currentBlock.Move(0, 1);
        if(IsBlockOutside() || BlockFits() == false) currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown()
{
    if(!gameOver) {
        currentBlock.Move(1, 0);
        if(IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}


void Game::LockBlock()
{
    vector<Posicion> tiles = currentBlock.GetCellPosicions();
    for(Posicion item: tiles) grid.grid[item.row][item.column] = currentBlock.id;
    currentBlock = nextBlock;
    if(BlockFits() == false) {gameOver = true; wait=true; SaveScore();}
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearAllFullRows();
    if(rowsCleared != 0) {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

void Game::Reset()
{
    grid.inicialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::SaveScore()
{
    ofstream scores("gamefiles/scores.txt", ios::app);
    scores<<playerName<<endl;
    scores<<score<<endl;
    scores.close();
}

void Game::RotateBlock()
{
    if(!gameOver) {
        currentBlock.Rotation();
        if(IsBlockOutside() || BlockFits() == false) currentBlock.UndoRotation();
        else PlaySound(rotateSound);
    }
}

bool Game::BlockFits()
{
    vector<Posicion> tiles = currentBlock.GetCellPosicions();
    for(Posicion item: tiles) {
        if(grid.IsCellEmpty(item.row, item.column) == false) return false;
    }
    return true;
}
