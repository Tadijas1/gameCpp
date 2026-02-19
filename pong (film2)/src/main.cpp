#include <iostream>
#include <raylib.h>

using namespace std;

//Deklarowanie zmiennych globalnych
int player_score = 0, cpu_score = 0;
Color green = Color{38, 185, 154, 255};
Color dark_green = Color{15, 120, 100, 255};
Color light_green = Color{129, 204, 184, 255};
Color yellow = Color{243, 213, 91, 255};
Color blue = Color{0, 30, 100, 255};

class Ball
{
    public:
    float x, y;
    int radius;
    int speed_x, speed_y;

    void draw()
    {
        DrawCircle(x, y, radius, yellow);
    }

    void update()
    {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0) speed_y *= -1;

        if(x + radius >= GetScreenWidth()){cpu_score++; resrtBall();} //cpu wins
        if(x-radius <= 0){player_score++; resrtBall();} //player wins
    }

    void resrtBall()
    {
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_chioces[2] = {-1, 1};
        speed_x *= speed_chioces[GetRandomValue(0,1)];
        speed_y *= speed_chioces[GetRandomValue(0,1)];
        speed_x++;
        speed_y++;  
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
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, blue);
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
    //Deklarowanie zmiennych lokalnych
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
        //1. Update pozycji 
        ball.update();
        player.update();
        cpu.update(ball.y);

        //2. Sprawdzanie kolozji
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) ball.speed_x *= -1;
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) ball.speed_x *= -1;

        //3. Rysowanie następnej klatki
        BeginDrawing();
        ClearBackground(dark_green);

        DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, green);
        DrawCircle(screen_width/2, screen_height/2, 125, light_green);

        ball.draw();

        player.draw();

        cpu.draw();
        player.draw();

        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);

        DrawText(TextFormat("%i", cpu_score), screen_width/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3*screen_width/4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// y_center = screen_height/2 - rectangle_height/2
// x_center = screen_width/2 - rectangle_width/2