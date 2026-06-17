#include "game.hpp"
#include <random>

bool Game::IsBlockOutside()
{
    vector<Posicion> tiles = currentBlock.GetCellPosicions();
    for(Posicion item: tiles) {
        if(grid.IsCellOutside(item.row, item.column)) return true;
    }
    return false;
}

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
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
    currentBlock.draw();
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
        break;
        case KEY_UP:
            RotateBlock();
        break;
    }
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
    if(BlockFits() == false) gameOver = true;
    nextBlock = GetRandomBlock();
    grid.ClearAllFullRows();
}

void Game::Reset()
{
    grid.inicialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

void Game::RotateBlock()
{
    if(!gameOver) {
        currentBlock.Rotation();
        if(IsBlockOutside() || BlockFits() == false) currentBlock.UndoRotation();
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
