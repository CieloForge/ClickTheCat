#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>

typedef struct {
    Sound meowSound;
    Sound wilhelmSound;
    Music bgmMusic;
} AudioResources;

// Function declarations
AudioResources CreateAudioResources();
void PlayMeowSound(AudioResources* audio);
void PlayWilhelmSound(AudioResources* audio);
void StartBGM(AudioResources* audio);
void StopBGM(AudioResources* audio);
void CleanupAudio(AudioResources* audio);

#endif