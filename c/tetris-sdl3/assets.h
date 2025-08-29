#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "music.h"
#include "sound.h"
#include "texture.h"

typedef struct {
    Texture block;
    Texture mini_block;
    Texture grid;
    Texture main_menu_bg;

    TTF_Font *default_font;

    Music main_music;

    Sound erase_lines_sound;
    Sound fit_tetromino_sound;
    Sound game_over_sound;
    Sound game_start_sound;
    Sound menu_open_sound;
    Sound move_tetromino_sound;
    Sound rotate_tetromino_sound;
} Assets;

void assets_load(Assets *assets, SDL_Renderer *renderer);
void assets_destroy(Assets *assets);

#endif // ASSETS_H
