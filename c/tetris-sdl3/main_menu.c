#include "main_menu.h"

#include "config.h"
#include "music.h"
#include "sprite.h"

static Text create_game_start_text(TTF_Font *font, SDL_Renderer *renderer)
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

    *menu = (MainMenu){ .background = { .texture = assets->main_menu_bg,
                                        .position = { 46, 239 } },
                        .main_music = { .mix_music = assets->main_music,
                                        .volume = 70.0f },
                        .game_start_text = create_game_start_text(
                            assets->default_font, renderer) };

    music_play(&menu->main_music);
}

void main_menu_quit(MainMenu *menu)
{
    text_destroy(&menu->game_start_text);
    music_stop();
}

void main_menu_process_events(MainMenu *menu, SDL_Event *event)
{
}

void main_menu_update(MainMenu *menu)
{
}

void main_menu_render(MainMenu *menu, SDL_Renderer *renderer)
{
    sprite_render(&menu->background, renderer);
    text_render(&menu->game_start_text, renderer);
}
