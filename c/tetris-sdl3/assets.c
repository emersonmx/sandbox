#include "assets.h"

void assets_load(Assets *assets, SDL_Renderer *renderer)
{
    assets->block = texture_from_file(renderer, "assets/block.png");
    assets->mini_block = texture_from_file(renderer, "assets/mini_block.png");
    assets->grid = texture_from_file(renderer, "assets/grid.png");
    assets->main_menu_bg =
        texture_from_file(renderer, "assets/main_menu_bg.png");

    assets->default_font = font_from_file("assets/Chewy.ttf", 24);

    assets->main_music = music_from_file("assets/main_music.ogg");

    assets->erase_lines_sound = sound_from_file("assets/erase_lines.wav");
    assets->fit_tetromino_sound = sound_from_file("assets/fit_tetromino.wav");
    assets->game_over_sound = sound_from_file("assets/game_over.wav");
    assets->game_start_sound = sound_from_file("assets/game_start.wav");
    assets->menu_open_sound = sound_from_file("assets/menu_open.wav");
    assets->move_tetromino_sound = sound_from_file("assets/move_tetromino.wav");
    assets->rotate_tetromino_sound =
        sound_from_file("assets/rotate_tetromino.wav");
}

void assets_destroy(Assets *assets)
{
    texture_destroy(&assets->block);
    texture_destroy(&assets->mini_block);
    texture_destroy(&assets->grid);
    texture_destroy(&assets->main_menu_bg);

    font_destroy(&assets->default_font);

    music_destroy(&assets->main_music);

    sound_destroy(&assets->erase_lines_sound);
    sound_destroy(&assets->fit_tetromino_sound);
    sound_destroy(&assets->game_over_sound);
    sound_destroy(&assets->game_start_sound);
    sound_destroy(&assets->menu_open_sound);
    sound_destroy(&assets->move_tetromino_sound);
    sound_destroy(&assets->rotate_tetromino_sound);
}
