#ifndef MAIN_MENU
#define MAIN_MENU

#include <SDL2/SDL.h>
#include <SDL_mixer.h>

#include "texture.h"

typedef struct {
    struct {
        Texture *texture;
        SDL_Point position;
    } background;
    struct {
        Mix_Music *music;
        float volume;
    } main_music;
} MainMenu;

void main_menu_init(MainMenu *menu);
void main_menu_quit(MainMenu *menu);
void main_menu_process_events(MainMenu *menu, SDL_Event *event);
void main_menu_update(MainMenu *menu);
void main_menu_render(MainMenu *menu, SDL_Renderer *renderer);

#endif // MAIN_MENU
