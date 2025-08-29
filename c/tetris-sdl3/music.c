#include "resources.h"

Music music_from_file(const char *file_path)
{
    SDL_Log("Loading music: %s", file_path);

    Mix_Music *music = Mix_LoadMUS(file_path);
    if (!music) {
        SDL_Log("Failed to load music %s: %s", file_path, Mix_GetError());
    }

    return (Music){
        .mix_music = music,
    };
}

void music_destroy(Music *music)
{
    if (music) {
        Mix_FreeMusic(music->mix_music);
        *music = (Music){ 0 };
    }
}

void music_play(Music *music)
{
    Mix_Music *mix_music = music->mix_music;

    bool err = Mix_PlayMusic(mix_music, -1) < 0;
    if (err) {
        SDL_Log("Couldn't play main menu music: %s", Mix_GetError());
        return;
    }
}

void music_stop()
{
    Mix_HaltMusic();
}
