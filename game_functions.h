#include <raylib.h>

#define SCREEN_WIDTH 1190
#define SCREEN_HEIGHT 910
#define STR 21
#define RANKING 10
#define FPS 60
#define VIDAS 3
#define BMAN_WIDTH 45
#define BMAN_HEIGHT 65
#define VELOCIDADE 4
#define KILL_POINTS 100
#define SIDES 4
#define BOOM 5
#define X 15
#define Y 11
#define BLOCO 70
#define N_TEXTURAS 6
#define N_BLOCOS 35
#define N_MUROS 40
#define N_INIMIGOS 20
#define N_BOMBAS 30

typedef struct
{
    Rectangle rec;
    int lives;
    float points;
    char name[STR];

}BOMBERMAN;

typedef enum
{
    morto,
    vivo

}STATUSINIMIGO;

typedef struct
{
    Rectangle rec;
    STATUSINIMIGO status;

}ENEMY;

typedef enum
{
    inata,
    ativa,
    explodindo,
    detonada

}STATUSBOMBA;

typedef struct
{
    Rectangle rec;
    STATUSBOMBA status;

}BOMB;

typedef struct
{
    Rectangle rec;
    int status;

}WALL;

typedef enum
{
    muro,
    porta,
    encontrada

}STATUSPORTA;

typedef struct
{
    Rectangle rec;
    STATUSPORTA status;

}DOOR;

typedef struct
{
    char name[STR];
    float points;
    double time;
    
}PLAYERFILE;

//Funcoes de jogo:
void GameLoop (BOMBERMAN *bomberman);
void LevelPassed (short *gameState, int *level);
void GetName (char name[STR], int *namePos, short *gameState);
void RankingFile (BOMBERMAN bomberman, double time, short *gameState, PLAYERFILE *player, PLAYERFILE ranking[RANKING]);
void BubbleSort (PLAYERFILE ranking[RANKING]);
void PrintFile (PLAYERFILE ranking[RANKING], BOMBERMAN *bman, short *gameState, int *level, double *time);
void GenLevel
(short *game, int level, BOMBERMAN *bman, ENEMY enemies[], int *nEnemies, BOMB bombs[], int *nBombs, int *bombsLeft, WALL muros[], int *nWalls, DOOR *door, int array[X][Y]);
void ResetWalls (WALL muros[N_MUROS]);
void ResetEnemies(ENEMY enemyList[N_INIMIGOS]);
void ResetArray (int gameArray[X][Y]);
void FillArray (int gameArray[X][Y]);
int IncrInt (int i, int incr, int limit);
void GameOver (short *gameState, int *level, double *time, BOMBERMAN *bomberman);
void ResetLevel (short *gameState);
void Restart (short *gameState, int *level, double *time, BOMBERMAN *bomberman);
void Pause (int *pause);
void GameInfo (BOMBERMAN bomberman, DOOR door, int level, int bombs, double time);
void FillBlocks (Rectangle blocos[N_BLOCOS], int gameArray[X][Y]);
void RandWalls (WALL muros[N_MUROS], int tam, int gameArray[X][Y]);
short GenWall (WALL *muro, int x, int y, int gameArray[X][Y]);
void BreakWalls (Rectangle explosions[BOOM], BOMBERMAN *bman, WALL muros[], int len);
void FindDoor (Rectangle explosions[SIDES], DOOR *door);
void GenDoor (DOOR *door, int gameArray[X][Y]);
void StatusDoor (DOOR *door, ENEMY enemyList[], int len);
//Funcoes de inimigos:
void RandEnemy (ENEMY enemyList[], int len, int gameArray[X][Y]);
short GenEnemy (ENEMY *enemy, int x, int y, int gameArray[X][Y]);
short CheckCollisionEnemy (Rectangle bmanRect, ENEMY enemyList[], int len);
void MoveEnemy (ENEMY enemies[N_INIMIGOS], int len, BOMBERMAN bman, Rectangle blocos[N_BLOCOS], Rectangle sides[SIDES], WALL muros[N_MUROS], int lenW, DOOR door, float speed);
void KillEnemies (Rectangle explosions[BOOM], BOMBERMAN *bman, ENEMY enemies[], int lenE);
//Funcoes de bomba:
void ResetBombs (BOMB bombList[], int tam);
void DropBomb (BOMB bombList[], int tam, BOMBERMAN bomberman, int *bombs);
short PositionBomb (BOMB *bomb, BOMBERMAN bomberman);
void ExplodeBombs (BOMB bombList[], int lenB, BOMBERMAN *bman, ENEMY enemies[], int lenE, WALL muros[], int lenW, DOOR *door, short *gameover, float *timer);
void DetonateBomb (BOMB *bomb, BOMBERMAN *bman, ENEMY enemies[], int lenE, WALL muros[], int lenW, DOOR *door, short *gameover, float *timer);
void ExplodeBomberman (BOMBERMAN *bomberman, Rectangle explosions[BOOM], short *gameover);
//Funcoes de movimento dos personagens:
short PlayerMovement (BOMBERMAN *bomberman, ENEMY enemyList[], int lenE, Rectangle sides[], Rectangle blocos[], WALL muros[N_MUROS], int lenW, DOOR door);
void MoveRight (Rectangle *rec, Rectangle blocos[N_BLOCOS], Rectangle sideR, WALL muros[N_MUROS], int lenW, DOOR door, short *game, float velocidade);
void MoveLeft (Rectangle *rec, Rectangle blocos[N_BLOCOS], Rectangle sideL, WALL muros[N_MUROS], int lenW, DOOR door, short *game, float velocidade);
void MoveUp (Rectangle *rec, Rectangle blocos[N_BLOCOS], Rectangle sideU, WALL muros[N_MUROS], int lenW, DOOR door, short *game, float velocidade);
void MoveDown (Rectangle *rec, Rectangle blocos[N_BLOCOS], Rectangle sideD, WALL muros[N_MUROS], int lenW, DOOR door, short *game, float velocidade);
void CheckCollisionWalls (Rectangle rec, WALL muros[N_MUROS], int len, short *collision);
void CheckCollisionDoor (Rectangle rec, DOOR door, short *collision, short *game);
//Funcoes de desenho:
void DrawEnemy (ENEMY enemyList[N_INIMIGOS], int len, Texture2D tex);
void DrawRecs (Rectangle listRec[], int tam);
void DrawBomb (BOMB bombList[], int tam, Texture2D bombTex);
void DrawExplosions (Rectangle explosions[BOOM]);
void DrawWalls (WALL muros[N_MUROS], int tam, Texture2D tex);
void DrawDoor (DOOR door, Texture2D wallTex, Texture2D doorTex);
void DrawBlocoTex (Rectangle blocos[], Texture2D tex);