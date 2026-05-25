#include "player.h"
#include <constants.h>
#include <raymath.h>


Player CreatePlayer(int x, int y, int speed) {
    Player player = {
        .x = x,
        .y = y,
        .moveSpeed = speed,
        .score = 0,
        .showMeowText = false,
        .meowTextTimer = 0.0f
    };
    return player;
}

void UpdatePlayer(Player* player) {
    // Update meow text timer
    if (player->showMeowText && player->meowTextTimer > 0.0f) {
        player->meowTextTimer -= GetFrameTime();
        if (player->meowTextTimer <= 0.0f) {
            player->showMeowText = false;
        }
    }
}

void HandlePlayerInput(Player* player) {
    if (IsKeyDown(KEY_A)) {
        player->x -= player->moveSpeed;
    }
    if (IsKeyDown(KEY_D)) {
        player->x += player->moveSpeed;
    }
    if (IsKeyDown(KEY_W)) {
        player->y -= player->moveSpeed;
    }
    if (IsKeyDown(KEY_S)) {
        player->y += player->moveSpeed;
    }
}

void UpdatePlayerBounds(Player* player, Sound* bounceSound) {
    // X boundaries
    if (player->x >= GAME_WIDTH - BOUNDARY_PADDING) {
        player->x -= BOUNCE_AMOUNT;
        PlaySound(*bounceSound);
    } 
    else if (player->x <= BOUNDARY_PADDING) {
        player->x += BOUNCE_AMOUNT;
        PlaySound(*bounceSound);
    }
    
    // Y boundaries
    if (player->y >= GAME_HEIGHT - BOUNDARY_PADDING) {
        player->y -= BOUNCE_AMOUNT;
        PlaySound(*bounceSound);
    }
    else if (player->y <= BOUNDARY_PADDING) {
        player->y += BOUNCE_AMOUNT;
        PlaySound(*bounceSound);
    }
}

void DrawPlayer(Player* player, Vector2 mousePos) {
    DrawCat(player->x, player->y, mousePos);
    
    if (player->showMeowText) {
        DrawText("Meow!!", player->x + 50, player->y - 100, 30, VIOLET);
    }
}

void ResetPlayer(Player* player) {
    player->x = PLAYER_INITIAL_X;
    player->y = PLAYER_INITIAL_Y;
    player->score = 0;
    player->showMeowText = false;
    player->meowTextTimer = 0.0f;
}

void CreateParticles(Player* player, Vector2 clickPos, Particle particles[], int maxParticles) {
    for (int i = 0; i < maxParticles; i++) {
        particles[i].position = (Vector2){player->x, player->y};
        particles[i].color = (Color){255, 0, 255, 255}; // Purple
        particles[i].life = 1.0f;
    }
}