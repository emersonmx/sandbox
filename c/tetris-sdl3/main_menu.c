#include "main_menu.h"

#include "SDL_mixer.h"
#include "SDL_render.h"

static void play_music(Mix_Music *music, float volume);

void main_menu_init(MainMenu *menu)
{
    play_music(menu->main_music.music, menu->main_music.volume);
}

static void play_music(Mix_Music *music, float volume)
{
    bool err = Mix_PlayMusic(music, -1) < 0;
    if (err) {
        SDL_Log("Couldn't play main menu music: %s", Mix_GetError());
        return;
    }

    err = Mix_VolumeMusic((int)(MIX_MAX_VOLUME * volume) / 100) < 0;
    if (err) {
        SDL_Log("Couldn't set main menu music volume: %s", Mix_GetError());
    }
}

void main_menu_quit(MainMenu *menu)
{
    Mix_HaltMusic();
}

void main_menu_process_events(MainMenu *menu, SDL_Event *event)
{
}

void main_menu_update(MainMenu *menu)
{
}

void main_menu_render(MainMenu *menu, SDL_Renderer *renderer)
{
    SDL_Point position = {
        .x = menu->background.position.x,
        .y = menu->background.position.y,
    };
    texture_render(menu->background.texture, renderer, position);
}
