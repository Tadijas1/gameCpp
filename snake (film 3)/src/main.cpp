#include <raylib.h>
#include <deque>

using namespace std;

//zmienne globalne
Color lightGreen = Color {173, 204, 96, 255};
Color darkGreen = Color {43, 51, 24, 255};
float cellSize = 30, cellCount = 25;

class Food
{
    public:
    Vector2 position = {5, 6};
    Texture2D texture;

    Food()
    {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void draw()
    {
        DrawTexture(texture, position.x*cellSize, position.y*cellSize, WHITE);
    }
};

class Snake
{
    public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    void draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x*cellSize, y*cellSize, cellSize, cellSize};
            DrawRectangleRounded(segment, 0.8, 6, darkGreen);
        }
        
    }
};

int main()
{
    //TWORZENIE OKNA
    InitWindow(cellSize*cellCount, cellSize*cellCount, "Snake");

    //FPS
    SetTargetFPS(60);

    //TWORZENIE OBIEKTÓW
    Food food = Food();
    Snake snake = Snake();

    //PĘTLA GRY
    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        //1. Update obiektów

        //2. Kolizie

        //3. Rysowanie następniej klatki
        ClearBackground(lightGreen);
        food.draw();  
        snake.draw();

        EndDrawing();
    }

    CloseWindow();
}