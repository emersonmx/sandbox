#include "main_menu.h"

#include "config.h"
#include "mini_blocks.h"
#include "music.h"
#include "sprite.h"

static Text create_game_start_text(Font font, SDL_Renderer *renderer)
{
    Text game_start_text = {
        .font = font,
        .color = { 255, 255, 255, 255 },
        .position = { .x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 1.3f },
        .content = "PRESS ENTER KEY TO START",
    };
    text_update(&game_start_text, renderer);
    game_start_text.offset = (SDL_Point){
        .x = game_start_text.texture.region.w / 2,
        .y = game_start_text.texture.region.h / 2,
    };
    return game_start_text;
}

void main_menu_init(MainMenu *menu, MainMenuInitOptions options)
{
    Assets *assets = options.assets;
    SDL_Renderer *renderer = options.renderer;

    *menu = (MainMenu){
        .image_background = {
            .texture = assets->main_menu_bg,
            .position = { 48, 240 },
        },
        .mini_blocks_background = {
            .texture = mini_blocks_create(assets->mini_block, renderer),
            .position = { 0, 0 },
        },
        .main_music = assets->main_music,
        .game_start_text = create_game_start_text(assets->default_font, renderer),
        .game_start_sound = assets->game_start_sound,
    };

    music_play(&menu->main_music);
}

void main_menu_quit(MainMenu *menu)
{
    text_destroy(&menu->game_start_text);
    texture_destroy(&menu->mini_blocks_background.texture);
}

void main_menu_process_events(MainMenu *menu, SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN) {
        SDL_Keycode key = event->key.keysym.sym;
        if (key == SDLK_RETURN || key == SDLK_KP_ENTER) {
            sound_play(&menu->game_start_sound);
        }
    }
}

void main_menu_render(MainMenu *menu, SDL_Renderer *renderer)
{
    sprite_render(&menu->mini_blocks_background, renderer);
    sprite_render(&menu->image_background, renderer);
    text_render(&menu->game_start_text, renderer);
}
