#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "cat.h"

// Add forward declaration
void DrawCat(int catX, int catY, Vector2 mousePos);

typedef struct {
    int x;
    int y;
    int moveSpeed;
    int score;
    bool showMeowText;
    float meowTextTimer;
} Player;

typedef struct {
    Vector2 position;
    Color color;
    float life;
} Particle;

// Function declarations
Player CreatePlayer(int x, int y, int speed);
void UpdatePlayer(Player* player);
void HandlePlayerInput(Player* player);
void UpdatePlayerBounds(Player* player, Sound* bounceSound);
void DrawPlayer(Player* player, Vector2 mousePos);
void ResetPlayer(Player* player);


#endif