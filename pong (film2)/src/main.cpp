#include <iostream>
#include <raylib.h>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace std;

//Deklarowanie zmiennych globalnych
int player_score = 0, cpu_score = 0;
Color green = Color{38, 185, 154, 255};
Color dark_green = Color{15, 120, 100, 255};
Color light_green = Color{129, 204, 184, 255};
Color yellow = Color{243, 213, 91, 255};
Color blue = Color{0, 30, 100, 255};
float timer = 0;

class Ball
{
    public:
    float x, y;
    int radius;
    float speed_x, speed_y;

    void draw()
    {
        DrawCircle(x, y, radius, yellow);
    }

    void update(float &p, float &c)
    {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0) speed_y *= -1;

        if(x + radius >= GetScreenWidth()){cpu_score++; resrtBall(p, c);} //cpu wins
        if(x-radius <= 0){player_score++; resrtBall(p, c);} //player wins
    }

    void resrtBall(float &player_s, float &cpu_s)
    {
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        speed_x = 7;
        speed_y = 7;

        player_s = 6;
        cpu_s = 6;

        int speed_chioces[2] = {-1, 1};
        speed_x *= speed_chioces[GetRandomValue(0,1)];
        speed_y *= speed_chioces[GetRandomValue(0,1)];

        timer = 0;
        
        // Coś tu jeszcze nie działa
        //float direction_choise[2] = {-0.5, 0.5};
        // speed_x += direction_choise[GetRandomValue(0,2)];
        // speed_y += direction_choise[GetRandomValue(0,2)];
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
    float speed;
    string name = "";

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

class CpuPaddle :public Paddle
{
    public:
    void update(int ball_y, char w)
    {
        if(w == '1'){
            if(y + height/2 > ball_y) y -= speed;
            if(y + height/2 < ball_y) y += speed;
        } else {
            if(IsKeyDown(KEY_S)) y += speed;
            if(IsKeyDown(KEY_W)) y -= speed;
        }

        limitMovment();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

void morespeed(char w)
{
    if(ball.speed_x < 0) ball.speed_x--;
    else ball.speed_x++;
    if(ball.speed_y < 0) ball.speed_y--;
    else ball.speed_y++;

    player.speed += 0.5;
    if(w == '1')cpu.speed += 0.7;
    else cpu.speed += 0.5;
    return;
}

int main()
{
    //Deklarowanie zmiennych lokalnych
    const int screen_width = 1200, screen_height = 800;

    //PYTANIE O TRYB
    bool exit = true;
    char wybor;
    while (exit)
    {
        system("cls"); //system("clear")
        cout<<"Wybierz tryb:"<<endl;
        cout<<"1. I gracz"<<endl;
        cout<<"2. II graczy"<<endl;
        wybor = getch(); cout<<endl;
        if((wybor == '1')||(wybor == '2')) exit = false;
    }
    
    system("cls"); //system("clear")
    cout<<"Wpisz nazwe gracza 1: "; cin>>player.name;
    if(wybor == '2') {cout<<"Wpisz nazwe gracza 2: "; cin>>cpu.name;}
    else if (wybor == '1') cpu.name = "CPU";

    //sprawdzanie czy nazwa nie jest za długa
    if((player.name.size() > 7)||(cpu.name.size() > 7)){
        system("cls"); //system("clear")
        cout<<"Niepoprawna nazwa gracza (max 7 slow)"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        return 0;
    }

    //DO ILU PUNKTOW GRA
    int max_punkty;
    exit = true;
    while (exit)
    {
        system("cls"); //system("clear")
        cout<<"Do ilu punktow gracie? (1-15): "; cin>>max_punkty;
        if((max_punkty > 15)||(max_punkty <= 0)) {
            system("cls"); //system("clear")
            cout<<"Niepoprawna liczba!"<<endl;
            this_thread::sleep_for(chrono::seconds(2));
            return 0;
        }
        else exit = false;
    }



    //OKNO GRY
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

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        //Wygrana jakiegoś gracza jak zdobędzie daną liczbę punktów
        if((player_score == max_punkty)||(cpu_score == max_punkty)){
            string msg;
            if(player_score == max_punkty) msg = player.name+" wygrywa";
            else msg = cpu.name+" wygrywa";
            BeginDrawing();
            ClearBackground(dark_green);
            DrawText(msg.c_str(), screen_width/4, screen_height/2 - 40, 80, WHITE);
            EndDrawing();

            this_thread::sleep_for(chrono::seconds(4));
            break;
        }


        //1. Update pozycji
        timer += GetFrameTime();
        if(timer >= 1.5f) ball.update(player.speed, cpu.speed);
        player.update();
        cpu.update(ball.y, wybor);

        //2. Sprawdzanie kolozji
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {ball.speed_x *= -1; morespeed(wybor);}
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {ball.speed_x *= -1; morespeed(wybor);}

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