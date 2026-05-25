#include "audio.h"
#include <constants.h>
#include <raylib.h>
#include <raymath.h>
#include <meow.h>
#include <bgm.h>
#include <wilhelm.h>

// Rest of audio.c remains the same

AudioResources CreateAudioResources() {
    AudioResources audio = {0};
    
    // Load meow sound
    Wave meowWave = LoadWaveFromMemory(".wav", meow_wav, meow_wav_len);
    audio.meowSound = LoadSoundFromWave(meowWave);
    SetSoundVolume(audio.meowSound, SOUND_VOLUME);
    
    // Load wilhelm scream
    Wave wScream = LoadWaveFromMemory(".wav", WilhelmScream_wav, WilhelmScream_wav_len);
    audio.wilhelmSound = LoadSoundFromWave(wScream);
    SetSoundVolume(audio.wilhelmSound, SOUND_VOLUME - 0.25f);
    
    // Load background music
    audio.bgmMusic = LoadMusicStreamFromMemory(".wav", bgm_wav, bgm_wav_len);
    SetMusicVolume(audio.bgmMusic, MUSIC_VOLUME);
    audio.bgmMusic.looping = true;
    
    // Unload wave data as it's no longer needed
    UnloadWave(meowWave);
    UnloadWave(wScream);
    
    return audio;
}

void PlayMeowSound(AudioResources* audio) {
    PlaySound(audio->meowSound);
}

void PlayWilhelmSound(AudioResources* audio) {
    PlaySound(audio->wilhelmSound);
}

void StartBGM(AudioResources* audio) {
    PlayMusicStream(audio->bgmMusic);
}

void StopBGM(AudioResources* audio) {
    StopMusicStream(audio->bgmMusic);
}

void CleanupAudio(AudioResources* audio) {
    StopBGM(audio);
    UnloadMusicStream(audio->bgmMusic);
    UnloadSound(audio->meowSound);
    UnloadSound(audio->wilhelmSound);
}