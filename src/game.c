#include "game.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>


// TODO -  FIX HIGHSCORE CODE
// Removed as Highscore doesnt work
//#define HIGH_SCORE_FILE "/tmp/ctc_highscore.txt"


// int storedHighScore = 0;
// bool highScoreInitialized = false;

// int LoadHighScore() {
//     if (!highScoreInitialized) {
//         storedHighScore = 0; // Default to 0
        
//         FILE *file = fopen(HIGH_SCORE_FILE, "r");
//         if (file) {
//             // Try to read the high score
//             if (fscanf(file, "%d", &storedHighScore) == 1) {
//                 // Successfully read, storedHighScore now contains the value
//             } else {
//                 printf("WARNING: Invalid high score file format, using default 0\n");
//                 storedHighScore = 0;
//             }
//             fclose(file);
//         } else {
//             printf("INFO: No high score file found, using default 0\n");
//         }
        
//         highScoreInitialized = true;
//     }
//     printf("Loaded high score: %d (stored: %d)\n", storedHighScore, storedHighScore);
//     return storedHighScore;
// }

// void SaveHighScore(int score) {
//     storedHighScore = score;
    
//     FILE *file = fopen(HIGH_SCORE_FILE, "w");
//     if (!file) {
//         printf("ERROR: Cannot save high score to %s\n", HIGH_SCORE_FILE);
//         return;
//     }
    
//     fprintf(file, "%d", score);
//     fclose(file);
// }


Game CreateGame() {
    Game game = {
        .state = START_SCREEN,
        .currentTime = 0.0f,
        .startTime = 0.0f,
        .gameTime = GAME_DURATION,
        .score = 0,
        //.highScore = LoadHighScore() // Load from storage
    };
    return game;
}

void UpdateGame(Game* game, Player* player) {
    if (game->state == PLAYING) {
        game->currentTime = (float)GetTime() - game->startTime;
        
        // Check game over condition
        if (game->currentTime >= game->gameTime) {
            //UpdateHighScore(game);
            game->state = GAME_OVER;
        }
    }
    
    // Add random movement based on score
    if (game->state == PLAYING) {
        player->x += GetRandomValue(-player->score - 15, player->score + 15);
        player->y += GetRandomValue(-player->score - 15, player->score + 15);
    }
}

bool CheckPlayerHit(Player* player, Vector2 mousePos) {
    Vector2 cursorToCat = (Vector2){player->x - mousePos.x, player->y - mousePos.y};
    float distance = Vector2Length(cursorToCat);
    
    if (distance < PLAYER_HITBOX_RADIUS) {
        player->score++;
        player->showMeowText = true;
        player->meowTextTimer = MEOW_TEXT_DURATION;
        return true;
    }
    return false;
}

void DrawGame(const Game* game, Player* player, AudioResources* audio) {
    ClearBackground(BLACK);
    //printf("Current high score: %d\n", game->highScore);
    
    if (game->state == START_SCREEN) {
        DrawStartScreen();
    }
    else if (game->state == PLAYING) {
        DrawGameScreen(game, player);
    }
    else if (game->state == GAME_OVER) {
        DrawGameOverScreen(game, player);
    }
}

void DrawStartScreen() {
    DrawRectangle(GAME_X_OFFSET, GAME_Y_OFFSET, GAME_WIDTH, GAME_HEIGHT, RAYWHITE);
    DrawTextEx(GetFontDefault(), "CLICK THE CAT", 
               (Vector2){GAME_WIDTH/3, 150}, FONT_SIZE_LARGE, 1, MAROON);
    DrawTextEx(GetFontDefault(), "Instructions:", 
               (Vector2){200, 250}, FONT_SIZE_MEDIUM, 1, BLACK);
    DrawTextEx(GetFontDefault(), "- Use WASD to move the cat", 
               (Vector2){200, 300}, FONT_SIZE_SMALL, 1, DARKGRAY);
    DrawTextEx(GetFontDefault(), "- Click on the cat before time runs out!", 
               (Vector2){200, 340}, FONT_SIZE_SMALL, 1, DARKGRAY);
    DrawTextEx(GetFontDefault(), "- Don't let the cat escape the play area!", 
               (Vector2){200, 380}, FONT_SIZE_SMALL, 1, DARKGRAY);
    DrawTextEx(GetFontDefault(), "Press ENTER to start", 
               (Vector2){GAME_WIDTH/3, 500}, FONT_SIZE_MEDIUM, 1, MAROON);
}

void DrawGameScreen(const Game* game, Player* player) {
    DrawRectangle(GAME_X_OFFSET, GAME_Y_OFFSET, GAME_WIDTH, GAME_HEIGHT, GRAY);
    
    // Draw score
    DrawTextEx(GetFontDefault(), TextFormat("Score: %i", player->score),
               (Vector2){SCREEN_WIDTH/2.5, 20}, FONT_SIZE_MEDIUM, 1, MAROON);

    // Draw high score
    // DrawTextEx(GetFontDefault(), TextFormat("High Score: %i", game->highScore),
    //            (Vector2){SCREEN_WIDTH/2.5, 80}, FONT_SIZE_MEDIUM, 1, MAROON);
    
    // Draw timer with color coding
    float remainingTime = game->gameTime - game->currentTime;
    Color timeColor = GetTimerColor(remainingTime / game->gameTime);
    DrawTextEx(GetFontDefault(), TextFormat("Time: %.1f", remainingTime),
               (Vector2){SCREEN_WIDTH/2.5, 50}, FONT_SIZE_MEDIUM, 1, timeColor);
    
    DrawPlayer(player, GetMousePosition());
}

void DrawGameOverScreen(const Game* game, Player* player) {
    DrawRectangle(GAME_X_OFFSET, GAME_Y_OFFSET, GAME_WIDTH, GAME_HEIGHT, RED);
    DrawTextEx(GetFontDefault(), "Game Over...", 
               (Vector2){GAME_WIDTH/3, GAME_HEIGHT/2}, FONT_SIZE_LARGE, 1.0f, RAYWHITE);
    DrawTextEx(GetFontDefault(), TextFormat("Your Final Score was: %i", player->score),
               (Vector2){GAME_WIDTH/3, GAME_HEIGHT/2 + 60}, FONT_SIZE_MEDIUM, 1, RAYWHITE);
    DrawTextEx(GetFontDefault(), "Press ENTER to restart", 
               (Vector2){GAME_WIDTH/3, GAME_HEIGHT/2 + 100}, FONT_SIZE_SMALL, 1, YELLOW);
}

Color GetTimerColor(float timePercentage) {
    if (timePercentage > 0.5f) {
        return GREEN;
    }
    else if (timePercentage > 0.25f) {
        return YELLOW;
    }
    else {
        return RED;
    }
}

void StartGame(Game* game, Player* player) {
    game->state = PLAYING;
    game->startTime = GetTime();
    game->currentTime = 0.0f;
    ResetPlayer(player);
}

void ResetGame(Game* game, Player* player) {
    game->state = PLAYING;
    // Save only if we broke the record
    // if (game->score > game->highScore) {
    //     game->highScore = game->score;
    //     //SaveHighScore(game->highScore);
    //     //storedHighScore = LoadHighScore();
    // }
    game->score = 0;
    game->startTime = GetTime();
    game->currentTime = 0.0f;
    ResetPlayer(player);
}

// void UpdateHighScore(Game* game) {
//     if (game->score > game->highScore) {
//         //printf("New high score: %d (saved to file)\n", game->score);
//         game->highScore = game->score;
//         //SaveHighScore(game->highScore);
//         //storedHighScore = LoadHighScore();
        
//     }
//     /* else – keep the existing highScore; do not rewrite the file */
// }