#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "texture.h"

typedef struct {
    Texture block;
    Texture mini_block;
    Texture grid;
    Texture main_menu_bg;

    TTF_Font *default_font;

    Mix_Music *main_music;
    Mix_Chunk *erase_lines_sound;
    Mix_Chunk *fit_tetromino_sound;
    Mix_Chunk *game_over_sound;
    Mix_Chunk *game_start_sound;
    Mix_Chunk *menu_open_sound;
    Mix_Chunk *move_tetromino_sound;
    Mix_Chunk *rotate_tetromino_sound;
} Assets;

void assets_load(Assets *assets, SDL_Renderer *renderer);
void assets_destroy(Assets *assets);

#endif // ASSETS_H
