#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

//zmienne globalne
Color lightGreen = Color {173, 204, 96, 255};
Color darkGreen = Color {43, 51, 24, 255};
float cellSize = 30, cellCount = 25, offset = 75;
double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (int i = 0; i < deque.size(); i++) if(Vector2Equals(deque[i], element)) return true;
    return false;    
}

class Food
{
    public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        this->position = GenerateRandomPos(snakeBody);
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void draw()
    {
        DrawTexture(texture, offset + position.x*cellSize, offset + position.y*cellSize, WHITE);
    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 positionNew = GenerateRandomCell();
        while (ElementInDeque(positionNew, snakeBody))
        {
            positionNew = GenerateRandomCell();
        }
        return positionNew;
    }
};

class Snake
{
    public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegmant = false;

    void draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{offset + x*cellSize, offset + y*cellSize, cellSize, cellSize};
            DrawRectangleRounded(segment, 0.8, 6, darkGreen);
        }
        
    }

    void update()
    {
        body.push_front(Vector2Add(body[0], direction));

        if(addSegmant == true) addSegmant = false;
        else body.pop_back();
    }

    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};

class Game
{
    public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game()
    {
        InitAudioDevice();
        eatSound = LoadSound("Sounds/eat.mp3");
        wallSound = LoadSound("Sounds/wall.mp3");
    }

    ~Game()
    {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void draw()
    {
        food.draw();
        snake.draw();
    }

    void update()
    {
        if(running){
            snake.update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood()
    {
        if(Vector2Equals(snake.body[0], food.position)) {food.position = food.GenerateRandomPos(snake.body); snake.addSegmant = true; score++; PlaySound(eatSound);}
    }

    void CheckCollisionWithEdges()
    {
        if(snake.body[0].x == cellCount || snake.body[0].x == -1) GameOver();
        if(snake.body[0].y == cellCount || snake.body[0].y == -1) GameOver();
    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        score = 0;
        running = false;
        PlaySound(wallSound);
    }

    void CheckCollisionWithTail()
    {
        for(int i = 1; i < snake.body.size(); i++) if(snake.body[0] == snake.body[i]) GameOver();
    }
};

bool eventTriggered(double interval)
{
    double currentTime = GetTime();

    if(currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

int main()
{
    //TWORZENIE OKNA
    InitWindow(2*offset + cellSize*cellCount, 2*offset + cellSize*cellCount, "Snake");

    //FPS
    SetTargetFPS(60);

    //TWORZENIE OBIEKTÓW
    Game game = Game();

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        //1. Update obiektów
        if(eventTriggered(0.2)) game.update();
        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {game.snake.direction = {1, 0}; game.running = true;}
        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {game.snake.direction = {-1, 0}; game.running = true;}
        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {game.snake.direction = {0, 1}; game.running = true;}
        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {game.snake.direction = {0, -1}; game.running = true;}
        //2. Kolizie

        //3. Rysowanie następniej klatki
        ClearBackground(lightGreen);
        DrawRectangleLinesEx(Rectangle{offset-5, offset-5, cellCount*cellSize+10, cellCount*cellSize+10}, 5, darkGreen);
        DrawText("Retro Snake", offset-5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset + cellSize*cellCount - 30, 20, 40, darkGreen);
        game.draw();

        EndDrawing();
    }

    CloseWindow();
}