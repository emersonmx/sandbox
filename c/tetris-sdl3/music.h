#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>

typedef struct {
    Mix_Music *mix_music;
} Music;

Music music_from_file(const char *file_path);
void music_destroy(Music *music);
void music_play(Music *music);
void music_stop();

#endif // MUSIC_H
