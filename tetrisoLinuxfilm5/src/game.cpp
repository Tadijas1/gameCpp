#include "game.hpp"
#include "colors.h"
#include "score.h"
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
    scores = GetScores();
    
    gameOver = false;
    gameOverTime = 0.0;
    canReset = false;
    player_score = 0;
    game_started = false;
    playerName = "Unnown player";
    BlockSpeed = 0.3;

    music_change = true;
    InitAudioDevice();
    orginal = LoadMusicStream("Sounds/orginal.mp3");
    tripoloski = LoadMusicStream("Sounds/tripoloski.mp3");
    chempions = LoadMusicStream("Sounds/chempions.mp3");
    gameOverMusic = LoadMusicStream("Sounds/game_over.mp3");
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    PlayMusicStream(orginal);
    PlayMusicStream(tripoloski);
    PlayMusicStream(chempions);
    PlayMusicStream(gameOverMusic);
}

Game::~Game()
{
    UnloadMusicStream(orginal);
    UnloadMusicStream(tripoloski);
    UnloadMusicStream(chempions);
    UnloadMusicStream(gameOverMusic);
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}

void Game::InitNicname()
{
    string nicname;

    while ((!IsKeyPressed(KEY_ENTER) || nicname.empty()) && WindowShouldClose() == false)
    {
        //Muzyka
        if(music_change) UpdateMusicStream(orginal);
        else UpdateMusicStream(tripoloski);

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

    playerName = nicname;
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

vector<Score> Game::GetScores()
{
    ifstream file("gamefiles/scores.txt");
    vector<Score> tab;
    string name;
    string score;

    //Odczywywanie z pliku
    while (getline(file, name) && getline(file, score))
    {
        Score s;
        s.name = name;
        s.score = stoi(score);
        tab.push_back(s);
    }
    file.close();

    //Sortowanie
    for(int i=0;i<tab.size();i++) {
		for(int j=1;j<tab.size()-i;j++) {
		    if(tab[j-1].score<tab[j].score) {
			    swap(tab[j-1], tab[j]);
            }
        }
    }

    //Zmioejszanie tablicy do 10
    while (tab.size() > 10)
    {
        tab.pop_back();
    }
    
    return tab;
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
        player_score += 100;
        break;
    case 2:
        player_score += 300;
        break;
    case 3:
        player_score += 500;
        break;
    case 4:
        player_score += 900;
        break;
    default:
        break;
    }

    player_score += moveDownPoints;
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && canReset) {
        gameOver = false;
        Reset();
        game_started = false;   
    }
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
        case KEY_LEFT_CONTROL:
        RotateBlock();
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
    if(BlockFits() == false) {
        gameOver = true;
        gameOverTime = GetTime();
        canReset = false;
        SaveScore(); 
        scores = GetScores();
        BlockSpeed = 0.305;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearAllFullRows();
    if(rowsCleared != 0) {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
    BlockSpeed -= 0.001;
}

void Game::Reset()
{
    grid.inicialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    player_score = 0;
}

void Game::SaveScore()
{
    ofstream file("gamefiles/scores.txt", ios::app);

    file<<playerName<<endl;
    file<<player_score<<endl;
    file.close();
}

void Game::ShowLiderboard()
{
    bool waiting = true;
    int repet;
    
    if(scores.size()<10) repet = scores.size();
    else repet = 10;
    
    while(WindowShouldClose() == false && waiting)
    {
        //Music
        UpdateMusicStream(chempions);

        int keyPressed = GetKeyPressed();
        int textPosY = 15;

        ClearBackground(darkBlue);
        BeginDrawing();
        for (int i = 0; i < repet; i++)
        {
            //How many space betwen number and name
            string space;
            if(i==9) space = ":  ";
            else space = ":   ";

            //What color to pick
            Color color;
            if(i == 0) color = yellow;
            else if(i == 1) color = silver;
            else if(i == 2) color = brown;
            else color = WHITE;
            string text = to_string(i+1) + space + scores[i].name + ": " + to_string(scores[i].score);
            DrawText(text.c_str(), 10, textPosY, 20, color);
            textPosY += 30;
        }
        DrawText("PRESS ANY KEY TO GO BACK...", 10, textPosY+20, 20, WHITE);
        EndDrawing();
        
        if(keyPressed != 0)waiting = false;
    }
    return;
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
