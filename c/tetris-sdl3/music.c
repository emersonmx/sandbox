#include "music.h"

void music_play(Music *music)
{
    Mix_Music *mix_music = music->mix_music;
    float volume = music->volume;

    bool err = Mix_PlayMusic(mix_music, -1) < 0;
    if (err) {
        SDL_Log("Couldn't play main menu music: %s", Mix_GetError());
        return;
    }

    err = Mix_VolumeMusic((int)(MIX_MAX_VOLUME * volume) / 100) < 0;
    if (err) {
        SDL_Log("Couldn't set main menu music volume: %s", Mix_GetError());
    }
}

void music_stop()
{
    Mix_HaltMusic();
}
