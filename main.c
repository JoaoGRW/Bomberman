#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include "game_functions.h"

int main (void)
{
    BOMBERMAN bomberman={{BLOCO + 1, BLOCO + 1, BMAN_WIDTH, BMAN_HEIGHT}, VIDAS, 0};

    GameLoop (&bomberman);

    return 0;
}

void GameLoop (BOMBERMAN *bomberman)
{
    int level=1;
    int namePos=0;
    short gameState=1;
    int gameArray[X][Y]={};
    int pause=1;
    int bombsLeft=level+2;
    int nWalls=level+4;
    int nBombs=level+2;
    int nEnemies=level+1;
    double time=0;
    float timer=0;

    PLAYERFILE player={};
    PLAYERFILE ranking[RANKING]={};

    Texture2D bomberman_png, bomb_active_png, bloco_png, enemy_png, wall_png, door_png;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "bomberman");
    SetTargetFPS(FPS);
    GetFontDefault();

    //Texturas
    bomberman_png=LoadTexture("../assets/Bomberman.png");
    bomb_active_png = LoadTexture ("../assets/Bombactive.png");
    bloco_png = LoadTexture ("../assets/Block.png");
    enemy_png = LoadTexture ("../assets/enemy.png");
    wall_png = LoadTexture ("../assets/Wall.png");
    door_png = LoadTexture ("../assets/Door.png");

    Vector2 bombermanpos={};

    BOMB bombList[N_BOMBAS]={};//Lista teste de bombas

    ENEMY enemyList[N_INIMIGOS]={};//Lista  de inimigos

    DOOR door={};

    //Paredes do cenario
    Rectangle sides[SIDES]={
        {SCREEN_WIDTH - BLOCO, 0, BLOCO, SCREEN_HEIGHT},
        {0, 0, BLOCO, SCREEN_HEIGHT},
        {0, 0, SCREEN_WIDTH, BLOCO},
        {0, SCREEN_HEIGHT - BLOCO, SCREEN_WIDTH, BLOCO}};

    WALL muros[N_MUROS]={};

    //Blocos do cenario
    Rectangle blocos[N_BLOCOS];
    FillBlocks (blocos, gameArray);
    RandWalls(muros, nWalls, gameArray);
    GenDoor(&door, gameArray);
    RandEnemy(enemyList, nEnemies, gameArray);

    //Loop do jogo
    while (!WindowShouldClose())
    {
        if (pause==1 && gameState==1)
        {
            time+=GetFrameTime();
            //Atualiza o vetor de posicao do bomberman (para passagem de parametros)
            bombermanpos.x=bomberman->rec.x;
            bombermanpos.y=bomberman->rec.y;

            //Movimento do bomberman e controle game over
            gameState = PlayerMovement (bomberman, enemyList, nEnemies, sides, blocos, muros, N_MUROS, door);

            //Movimento dos inimigos
            MoveEnemy(enemyList, nEnemies, *bomberman, blocos, sides, muros, nWalls, door, 1.0f);

            //Checa se deve posicionar uma bomba
            DropBomb(bombList, nBombs, *bomberman, &bombsLeft);

            //Checa se deve explodir as bombas posicionadas
            ExplodeBombs (bombList, nBombs, bomberman, enemyList, nEnemies, muros, nWalls, &door, &gameState, &timer);

            //Checa se deve mudar o status da porta
            StatusDoor (&door, enemyList, nEnemies);

        }

        GenLevel (&gameState, level, bomberman, enemyList, &nEnemies, bombList, &nBombs, &bombsLeft, muros, &nWalls, &door, gameArray);

        //Comeco do desenho
        BeginDrawing();
        ClearBackground(DARKGREEN);
        DrawRecs (sides, SIDES);
        DrawRecs (blocos, N_BLOCOS);
        DrawBlocoTex(blocos, bloco_png);
        DrawBomb (bombList, N_BOMBAS, bomb_active_png);
        DrawWalls(muros, nWalls, wall_png);
        DrawDoor (door, wall_png, door_png);
        DrawEnemy (enemyList, nEnemies, enemy_png);
        DrawRectangleRec(bomberman->rec, BLANK);
        DrawTextureEx (bomberman_png, bombermanpos, 0, 0.3, WHITE);

        Pause(&pause);
        LevelPassed(&gameState, &level);
        GameOver(&gameState, &level, &time, bomberman);
        GameInfo(*bomberman, door, level, bombsLeft, time);

        GetName(bomberman->name, &namePos, &gameState);
        RankingFile(*bomberman, time, &gameState, &player, ranking);
        PrintFile(ranking, bomberman, &gameState, &level, &time);

        EndDrawing();


    }
    CloseWindow();

    UnloadTexture(bomberman_png);
    UnloadTexture(bomb_active_png);
    UnloadTexture(bloco_png);
    UnloadTexture(enemy_png);

}
