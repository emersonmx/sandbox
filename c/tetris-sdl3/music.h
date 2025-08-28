#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>

typedef struct {
    Mix_Music *mix_music;
    float volume;
} Music;

void music_play(Music *music);
void music_stop();

#endif // MUSIC_H
