// Click the Cat
// CieloForge - Garbage Jam #4 Submission
// Version 0.3.0
// Garbage Jam #4 - (https://itch.io/jam/garbage-jam-4)
// Author: CieloForge (https://cieloforge.itch.io) or (https://github.com/cieloforge)

// Standard IN/OUTPUT Library
#include <stdio.h>
#include <stdlib.h> // Useful utility header


// Raylib - (https://raylib.com)
#include <raylib.h>
#include <raymath.h> // Raylibs math library

// Custom
#include "constants.h"
#include "player.h"
#include "audio.h"
#include "game.h"
#include "cat.h"


// To do area...
// TODO - FIX HIGHSCORE issue....
// TODO -  Make it a more appealing game.

// Initialize the Raylib engine
void InitRaylibEngine(int width, int height, const char* title, int targetFPS) {
    InitWindow(width, height, title);
    InitAudioDevice();
    SetTargetFPS(targetFPS);
}


int main(void) {
    // Initialize engine
    InitRaylibEngine(SCREEN_WIDTH, SCREEN_HEIGHT, "Click the Cat", MAX_FPS);
    
    // Create game objects
    Game game = CreateGame();
    Player player = CreatePlayer(PLAYER_INITIAL_X, PLAYER_INITIAL_Y, PLAYER_MOVE_SPEED);
    AudioResources audio = CreateAudioResources();
    
    // Start background music
    StartBGM(&audio);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update background music stream
        UpdateMusicStream(audio.bgmMusic);
        
        // Handle game state transitions
        if (IsKeyPressed(KEY_ENTER)) {
            if (game.state == START_SCREEN) {
                StartGame(&game, &player);
            }
            else if (game.state == GAME_OVER) {
                ResetGame(&game, &player);
                StartBGM(&audio);
            }
        }
        
        // Update game logic
        UpdateGame(&game, &player);
        UpdatePlayer(&player);
        
        // Handle player input and boundaries
        if (game.state == PLAYING) {
            HandlePlayerInput(&player);
            UpdatePlayerBounds(&player, &audio.wilhelmSound);
            
            // Check for player hit
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                if (CheckPlayerHit(&player, mousePos)) {
                    PlayMeowSound(&audio);
                }
            }
        }
        
        // Render
        BeginDrawing();
        DrawGame(&game, &player, &audio);
        
        // Debug overlay
        if (DEBUG) {
            DrawDebugInfo(&game);
        }
        
        EndDrawing();
    }
    
    // Cleanup
    CleanupAudio(&audio);
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}

void DrawDebugInfo(const Game* game) {
    DrawTextEx(GetFontDefault(), TextFormat("Current Time: %.1f", game->currentTime),
               (Vector2){18, 40}, FONT_SIZE_DEBUG, 1, VIOLET);
    DrawTextEx(GetFontDefault(), TextFormat("FPS: %i", GetFPS()),
               (Vector2){18, 20}, FONT_SIZE_DEBUG, 1, VIOLET);
    DrawTextEx(GetFontDefault(), "Debug Mode",
               (Vector2){18, 700}, FONT_SIZE_DEBUG, 1, VIOLET);
}