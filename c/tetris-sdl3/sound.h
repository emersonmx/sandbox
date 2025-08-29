#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>

typedef struct {
    Mix_Chunk *mix_chunk;
} Sound;

void sound_destroy(Sound *sound);
void sound_play(Sound *sound);
void sound_stop(Sound *sound);

#endif // SOUND_H
