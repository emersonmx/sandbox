#include "main_menu.h"

#include "SDL_render.h"
#include "music.h"
#include "sprite.h"

void main_menu_init(MainMenu *menu, Assets *assets)
{
    *menu = (MainMenu){
        .background = { .texture = &assets->main_menu_bg,
                        .position = { 46, 239 } },
        .main_music = { .mix_music = assets->main_music, .volume = 70.0f },
    };

    music_play(&menu->main_music);
}

void main_menu_quit(MainMenu *menu)
{
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
}
