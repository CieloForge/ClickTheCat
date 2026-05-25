#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "constants.h"
#include "player.h"
#include "audio.h"

typedef enum {
    START_SCREEN,
    PLAYING,
    GAME_OVER
} GameState;

typedef struct {
    GameState state;
    float currentTime;
    float startTime;
    float gameTime;
    int score;
    int highScore;
} Game;






void DrawStartScreen();
void DrawGameScreen(const Game* game, Player* player);
void DrawGameOverScreen(const Game* game, Player* player);
Game CreateGame();
void UpdateGame(Game* game, Player* player);
bool CheckPlayerHit(Player* player, Vector2 mousePos);
void DrawGame(const Game* game, Player* player, AudioResources* audio);
void StartGame(Game* game, Player* player);
void ResetGame(Game* game, Player* player);
void DrawDebugInfo(const Game* game);
Color GetTimerColor(float timePercentage);
void UpdateHighScore(Game* game);
void SaveHighScore(int score);

#endif