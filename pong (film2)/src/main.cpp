#include <iostream>
#include <raylib.h>

using namespace std;

class Ball
{
    public:
    float x, y;
    int radius;
    int speed_x, speed_y;

    void draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void update()
    {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0) speed_y *= -1;
        if(x + radius >= GetScreenWidth() || x-radius <= 0) speed_x *= -1;
    }
};

class Paddle
{
    protected:
    void limitMovment()
    {
        if(y <= 0) y=0;
        if(y >= GetScreenHeight() - height) y = GetScreenHeight() - height;
    }

    public:
    float x, y;
    float width, height;
    int speed;

    void draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void update()
    {
        if(IsKeyDown(KEY_DOWN)) y += speed;
        if(IsKeyDown(KEY_UP)) y -= speed;

        limitMovment();
    }
};

class CpuPddle :public Paddle
{
    public:
    void update(int ball_y)
    {
        if(y + height/2 > ball_y) y -= speed;
        if(y + height/2 < ball_y) y += speed;

        limitMovment();
    }
};

Ball ball;
Paddle player;
CpuPddle cpu;

int main()
{
    //Deklarowanie zmiennych
    const int screen_width = 1200, screen_height = 800;

    //Okno gry
    InitWindow(screen_width, screen_height, "Pong");
    //Liczba klatek
    SetTargetFPS(60);

    //Nadawanie wartości zmiennym należących do obiektów
    //BALL
    ball.radius = 20;
    ball.speed_x = 7; 
    ball.speed_y = 7;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    //PLAYER
    player.width = 25;
    player.height = 120;
    player.speed = 6;
    player.x = screen_width - player.width - 10;
    player.y = screen_height/2 - player.height/2;
    //CPU
    cpu.width = 25;
    cpu.height = 120;
    cpu.speed = 6;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;

    //Pętla gry
    while(WindowShouldClose() == false)
    {
        //1. Input z klawiatury, myszki itp.

        //2. Update pozycji
        ball.update();
        player.update();
        cpu.update(ball.y);

        //3. Rysowanie następnej klatki
        BeginDrawing();
        ClearBackground(BLACK);

        ball.draw();

        player.draw();

        cpu.draw();
        player.draw();

        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// y_center = screen_height/2 - rectangle_height/2
// x_center = screen_width/2 - rectangle_width/2