#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 20
#define CELL_SIZE 20
#define SCREEN_WIDTH (GRID_SIZE * CELL_SIZE)
#define SCREEN_HEIGHT (GRID_SIZE * CELL_SIZE)
#define MAX_SNAKE_LENGTH (GRID_SIZE * GRID_SIZE)
#define MOVE_DELAY 0.1f

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    Direction direction;
} Snake;

typedef struct {
    Position pos;
    bool active;
} Food;

typedef struct {
    Snake snake;
    Food food;
    bool gameOver;
    float moveTimer;
    int score;
} GameState;

void InitGame(GameState *game);
void UpdateGame(GameState *game, float deltaTime);
void DrawGame(const GameState *game);
void MoveSnake(GameState *game);
void CheckCollisions(GameState *game);
void SpawnFood(GameState *game);
void ResetGame(GameState *game);

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(60);
    
    srand(time(NULL));
    
    GameState game;
    InitGame(&game);
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        UpdateGame(&game, deltaTime);
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawGame(&game);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

void InitGame(GameState *game)
{
    game->snake.length = 3;
    game->snake.direction = DIR_RIGHT;
    
    for (int i = 0; i < game->snake.length; i++)
    {
        game->snake.body[i].x = GRID_SIZE / 2 - i;
        game->snake.body[i].y = GRID_SIZE / 2;
    }
    
    game->gameOver = false;
    game->moveTimer = 0;
    game->score = 0;
    
    SpawnFood(game);
}

void UpdateGame(GameState *game, float deltaTime)
{
    if (game->gameOver)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            ResetGame(game);
        }
        return;
    }
    
    if (IsKeyPressed(KEY_UP) && game->snake.direction != DIR_DOWN)
        game->snake.direction = DIR_UP;
    else if (IsKeyPressed(KEY_DOWN) && game->snake.direction != DIR_UP)
        game->snake.direction = DIR_DOWN;
    else if (IsKeyPressed(KEY_LEFT) && game->snake.direction != DIR_RIGHT)
        game->snake.direction = DIR_LEFT;
    else if (IsKeyPressed(KEY_RIGHT) && game->snake.direction != DIR_LEFT)
        game->snake.direction = DIR_RIGHT;
    
    game->moveTimer += deltaTime;
    if (game->moveTimer >= MOVE_DELAY)
    {
        game->moveTimer = 0;
        MoveSnake(game);
        CheckCollisions(game);
    }
}

void DrawGame(const GameState *game)
{
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int y = 0; y < GRID_SIZE; y++)
        {
            DrawRectangleLines(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
        }
    }
    
    for (int i = 0; i < game->snake.length; i++)
    {
        Color color = (i == 0) ? DARKGREEN : GREEN;
        DrawRectangle(game->snake.body[i].x * CELL_SIZE, 
                     game->snake.body[i].y * CELL_SIZE,
                     CELL_SIZE, CELL_SIZE, color);
    }
    
    if (game->food.active)
    {
        DrawRectangle(game->food.pos.x * CELL_SIZE,
                     game->food.pos.y * CELL_SIZE,
                     CELL_SIZE, CELL_SIZE, RED);
    }
    
    DrawText(TextFormat("Score: %d", game->score), 10, 10, 20, WHITE);
    
    if (game->gameOver)
    {
        DrawText("GAME OVER!", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 20, 30, RED);
        DrawText("Press SPACE to restart", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 + 20, 20, WHITE);
    }
}

void MoveSnake(GameState *game)
{
    Position newHead = game->snake.body[0];
    
    switch (game->snake.direction)
    {
        case DIR_UP:    newHead.y--; break;
        case DIR_DOWN:  newHead.y++; break;
        case DIR_LEFT:  newHead.x--; break;
        case DIR_RIGHT: newHead.x++; break;
    }
    
    for (int i = game->snake.length - 1; i > 0; i--)
    {
        game->snake.body[i] = game->snake.body[i - 1];
    }
    
    game->snake.body[0] = newHead;
}

void CheckCollisions(GameState *game)
{
    Position head = game->snake.body[0];
    
    if (head.x < 0 || head.x >= GRID_SIZE || head.y < 0 || head.y >= GRID_SIZE)
    {
        game->gameOver = true;
        return;
    }
    
    for (int i = 1; i < game->snake.length; i++)
    {
        if (head.x == game->snake.body[i].x && head.y == game->snake.body[i].y)
        {
            game->gameOver = true;
            return;
        }
    }
    
    if (game->food.active && head.x == game->food.pos.x && head.y == game->food.pos.y)
    {
        if (game->snake.length < MAX_SNAKE_LENGTH)
        {
            game->snake.length++;
            game->score += 10;
        }
        SpawnFood(game);
    }
}

void SpawnFood(GameState *game)
{
    bool validPosition;
    do {
        validPosition = true;
        game->food.pos.x = rand() % GRID_SIZE;
        game->food.pos.y = rand() % GRID_SIZE;
        
        for (int i = 0; i < game->snake.length; i++)
        {
            if (game->snake.body[i].x == game->food.pos.x && 
                game->snake.body[i].y == game->food.pos.y)
            {
                validPosition = false;
                break;
            }
        }
    } while (!validPosition);
    
    game->food.active = true;
}

void ResetGame(GameState *game)
{
    InitGame(game);
}