#include "sound.h"

void sound_destroy(Sound *sound)
{
    if (sound->mix_chunk) {
        Mix_FreeChunk(sound->mix_chunk);
        *sound = (Sound){ 0 };
    }
}

void sound_play(Sound *sound)
{
    bool err = Mix_PlayChannel(-1, sound->mix_chunk, 0) == -1;
    if (err) {
        SDL_Log("Couldn't play sound: %s", Mix_GetError());
    }
}

void sound_stop(Sound *sound)
{
    bool err = Mix_HaltChannel(-1) == -1;
    if (err) {
        SDL_Log("Couldn't stop sound: %s", Mix_GetError());
    }
}
