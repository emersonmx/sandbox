#include "assets.h"

#include <SDL_image.h>

#include "macros.h"

void assets_load(Assets *assets, SDL_Renderer *renderer)
{
    LOAD_IMAGE(renderer, assets->block, "assets/block.png");
    LOAD_IMAGE(renderer, assets->mini_block, "assets/mini_block.png");
    LOAD_IMAGE(renderer, assets->grid, "assets/grid.png");
    LOAD_IMAGE(renderer, assets->main_menu_bg, "assets/main_menu_bg.png");

    LOAD_FONT(assets->default_font, "assets/Chewy.ttf", 24);

    LOAD_MUSIC(assets->main_music, "assets/main_music.ogg");

    LOAD_SOUND(assets->erase_lines_sound, "assets/erase_lines.wav");
    LOAD_SOUND(assets->fit_tetromino_sound, "assets/fit_tetromino.wav");
    LOAD_SOUND(assets->game_over_sound, "assets/game_over.wav");
    LOAD_SOUND(assets->game_start_sound, "assets/game_start.wav");
    LOAD_SOUND(assets->menu_open_sound, "assets/menu_open.wav");
    LOAD_SOUND(assets->move_tetromino_sound, "assets/move_tetromino.wav");
    LOAD_SOUND(assets->rotate_tetromino_sound, "assets/rotate_tetromino.wav");
}

void assets_free(Assets *assets)
{
    FREE_IMAGE(assets->block);
    FREE_IMAGE(assets->mini_block);
    FREE_IMAGE(assets->grid);
    FREE_IMAGE(assets->main_menu_bg);

    FREE_FONT(assets->default_font);

    FREE_MUSIC(assets->main_music);

    FREE_SOUND(assets->erase_lines_sound);
    FREE_SOUND(assets->fit_tetromino_sound);
    FREE_SOUND(assets->game_over_sound);
    FREE_SOUND(assets->game_start_sound);
    FREE_SOUND(assets->menu_open_sound);
    FREE_SOUND(assets->move_tetromino_sound);
    FREE_SOUND(assets->rotate_tetromino_sound);
}
