// 2048 - پروژه‌ی برنامه‌نویسی مقدماتی

// دانشجویان باید منطق بازی را بر اساس امضای توابع و توضیحات موجود پیاده‌سازی کنند.
// رابط گرافیکی کامل است و نیازی به تغییر ندارد

#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 8
#define MAX_HISTORY 100

// --- ساختارهای داده ---
typedef struct
{
    int **board;   // ماتریس بازی که به صورت پویا تخصیص داده می‌شود (size x size)
    int size;      // اندازه‌ی صفحه‌ی بازی (مثلاً ۴ برای صفحه‌ی ۴ در ۴)
    int score;     // امتیاز فعلی
    bool gameOver; // مشخص می‌کند آیا بازی تمام شده یا نه
} GameState;

typedef struct
{
    GameState history[MAX_HISTORY]; // تاریخچه‌ی حالت‌های بازی برای undo/redo
    int current;                    // شماره‌ی حالت فعلی
    int last;                       // شماره‌ی آخرین حالت ذخیره‌شده
} History;


// --- مدیریت حافظه ---

// تخصیص حافظه برای ماتریس size x size و مقداردهی اولیه‌ی خانه‌ها به ۰
int **AllocateBoard(int size);

// آزادسازی حافظه‌ی ماتریس تخصیص داده‌شده
void FreeBoard(int **board, int size);

// کپی‌کردن محتویات ماتریس مبدا به مقصد (با فرض یکسان بودن اندازه)
void CopyBoard(int **dst, int **src, int size);

// --- مدیریت تاریخچه ---

// ذخیره‌سازی حالت فعلی بازی برای undo/redo
void SaveState(History *h, GameState *s);

// بازگشت به حالت قبلی بازی در صورت امکان
void Undo(GameState *s, History *h);

// رفتن به حالت بعدی در صورت وجود (redo)
void Redo(GameState *s, History *h);

// --- مقداردهی اولیه‌ی بازی ---

// اضافه‌کردن یک عدد تصادفی (۲ یا ۴) به یکی از خانه‌های خالی
void AddRandomTile(GameState *state);

// مقداردهی اولیه به بازی جدید با دو عدد تصادفی
void InitGame(GameState *state, int size);

// --- منطق بازی ---

// تلاش برای حرکت دادن صفحه در یکی از جهات
// dir: ۰ = بالا، ۱ = راست، ۲ = پایین، ۳ = چپ
// خروجی: اگر حرکت باعث تغییر صفحه شد true برمی‌گرداند
bool Move(GameState *state, int dir);

// بررسی اینکه آیا حرکت دیگری ممکن نیست (پایان بازی)
bool IsGameOver(GameState *state);

// (رابط گرافیکی فراهم شده - تغییر ندهید)
void DrawGame(GameState *state)
{
    int screenWidth = 600;
    int screenHeight = 700;
    BeginDrawing();
    ClearBackground(RAYWHITE);

    char scoreText[64];
    sprintf(scoreText, "Score: %d", state->score);
    DrawText(scoreText, 20, 20, 30, DARKGRAY);

    int gridSize = 500;
    int tileSize = gridSize / state->size;
    int offsetX = (screenWidth - gridSize) / 2;
    int offsetY = (screenHeight - gridSize) / 2 + 20;

    for (int i = 0; i < state->size; i++)
    {
        for (int j = 0; j < state->size; j++)
        {
            int value = state->board[i][j];
            Color tileColor = (value == 0) ? LIGHTGRAY : (Color){255 - value*4 % 255, 200 - value*4 % 200, 100 + value % 155, 255};
            int x = offsetX + j * tileSize;
            int y = offsetY + i * tileSize;
            DrawRectangle(x, y, tileSize - 5, tileSize - 5, tileColor);
            if (value > 0)
            {
                char buf[16];
                sprintf(buf, "%d", value);
                int fontSize = tileSize / 4;
                Vector2 textSize = MeasureTextEx(GetFontDefault(), buf, fontSize, 1);
                DrawText(buf, x + (tileSize - textSize.x) / 2, y + (tileSize - textSize.y) / 2, fontSize, BLACK);
            }
        }
    }

    if (state->gameOver)
    {
        DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0, 0, 0, 120});
        DrawText("Game Over!", 200, 300, 40, RED);
        DrawText("Press R to Restart", 160, 360, 30, DARKGRAY);
    }

    EndDrawing();
}

int main()
{
    int boardSize = 4; // برای نمره اضافه

    srand((unsigned int)time(NULL));
    InitWindow(600, 700, "2048");
    SetTargetFPS(60);

    GameState game;
    InitGame(&game, boardSize);

    History history = {0};
    SaveState(&history, &game);

    while (!WindowShouldClose())
    {
        if (!game.gameOver)
        {
            int move = -1;
            if (IsKeyPressed(KEY_UP))
                move = 0;
            else if (IsKeyPressed(KEY_RIGHT))
                move = 1;
            else if (IsKeyPressed(KEY_DOWN))
                move = 2;
            else if (IsKeyPressed(KEY_LEFT))
                move = 3;
            else if (IsKeyPressed(KEY_Z))
                Undo(&game, &history);
            else if (IsKeyPressed(KEY_Y))
                Redo(&game, &history);

            if (move != -1 && Move(&game, move))
            {
                SaveState(&history, &game);
                game.gameOver = IsGameOver(&game);
            }
        }
        else if (IsKeyPressed(KEY_R))
        {
            FreeBoard(game.board, boardSize);
            InitGame(&game, boardSize);
            history.current = history.last = 0;
            SaveState(&history, &game);
        }

        DrawGame(&game);
    }

    for (int i = 0; i <= history.last; i++)
    {
        FreeBoard(history.history[i].board, boardSize);
    }
    FreeBoard(game.board, boardSize);
    CloseWindow();
    return 0;
}

// دانشجویان باید تمام توابع مشخص‌ شده در بالا را در این بخش پیاده‌سازی کنند.
// ...

int** AllocateBoard(int size){

    int** board=(int**)malloc(size * 4);
    if (board == NULL)
    {
        printf("Error Memory  row!!");
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        board[i]=(int*)malloc(size * 4);

        if (board[i] == NULL)
        {
            printf("Error Memory col !!");
            return 1;

            for (int j = 0; j < size; i++)
            {
                free(board[j]);
            }
            free(board);
            return 1;
        }
        
    
    for (int j = 0; j < size; j++)
    {
        board[i][j]==0;
    }}
    return board;
    
}

void FreeBoard(int **board,int size){

    for (int  i = 0; i < size; i++)
    {
        free(board[i]);
    }
    
    free(board);

}

void AddRandomTile(GameState *state){

    int empty;

    for (int i = 0; i < state->size; i++)
    {
        for (int j = 0; j < state->size; j++)
        {
            if (state->board[i][j] == 0);
            
            empty=empty+1;
            
        }
        
    }

    int target = rand() % empty +1;

    int v;

    for (int i = 0; i < state->size; i++)
    {
        for (int j = 0; j < state->size; j++)
        {
            if (state->board[i][j] == 0)
            {
                v=v+1;

                if (v == target)
                {
                    int random = rand() % 10 ;
                    
                    if (random == 9)
                    {
                        state->board[i][j] = 4;
                    }
                    else
                    {
                        state->board[i][j] = 2 ;
                    }
                    
                }
                
            }
            
        }
        
    }
    
    

}

void InitGame(GameState *state, int size){

    state->score =0;
    state->gameOver =false;
    state->size=size;

    state->board =(int**)malloc(size * 4);
    if (state->board == NULL)
    {
        printf("Error Memory row");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        state->board[i] =(int*)malloc(size * 4);
        if (state->board[i] == NULL)
        {
            printf("Error Memory col");
            return;
        }
        
        for (int j = 0; j < size; j++)
        {
            state->board[i][j] = 0;
        }
        
    }
    
    AddRandomTile(state);
    AddRandomTile(state);
    
    
    
}

bool Move(GameState *state, int dir){
    
    if (dir == 0)
    {
        
    }
    else if (dir == 1)
    {
        
    }
    else if (dir == 2)
    {
        
    }
    else if (dir == 3)
    {
        bool movey =false;
        int lift = 0;

        for (int i = 0; i < state->size; i++)
        {
            for (int j = 0; j < state->size; j++)
            {
                if (state->board[i][j] != 0 )
                {
                    state->board[i][lift] = state->board[i][j];

                    if (j != lift)
                    {
                        state->board[i][j]= 0;
                        movey=true;
                    }
                    lift =lift+1;
                }
                
            }
            
        }
    }
    
}


bool IsGameOver(GameState *state){
    
    for (int i = 0; i < state->size; i++)
    {
        for (int j = 0; j < state->size; j++)
        {
            if (state->board[i][j] == 0)
            {
                return false;
            }
            
        }
        
    }
    

    for (int i = 0; i < state->size; i++)
    {
        for (int j = 0; j < state->size; j++)
        {
            if (state->board[i][j] != 0 )
            {
                if (j < state->size-1 && state->board[i][j]  == state->board[i][j+1])
                {
                 return false;
                    
                }

                if (i < state->size-1 &&  state->board[i][j] ==state->board[i+1][j] )
                {
                    return false;
                }
                
                
            }
            
        }
        
    }
    state->gameOver=true;
    return true;
}

void SaveState(History *h, GameState *s){

     
   
}