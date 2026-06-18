#include "game.hpp"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    wait=false;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    //music = LoadMusicStream("Sounds/tripoloski.mp3");
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
    if(gameOver && keyPressed != 0){ gameOver = false; Reset();}
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
    if(BlockFits() == false) {gameOver = true; wait=true;}
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
