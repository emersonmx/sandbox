#ifndef MAIN_MENU
#define MAIN_MENU

#include "assets.h"
#include "music.h"
#include "sprite.h"

typedef struct {
    Sprite background;
    Music main_music;
} MainMenu;

void main_menu_init(MainMenu *menu, Assets *assets);
void main_menu_quit(MainMenu *menu);
void main_menu_process_events(MainMenu *menu, SDL_Event *event);
void main_menu_update(MainMenu *menu);
void main_menu_render(MainMenu *menu, SDL_Renderer *renderer);

#endif // MAIN_MENU
