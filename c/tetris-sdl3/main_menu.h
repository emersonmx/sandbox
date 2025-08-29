#ifndef MAIN_MENU
#define MAIN_MENU

#include "assets.h"
#include "music.h"
#include "sprite.h"
#include "text.h"

typedef struct {
    Sprite image_background;
    Sprite mini_blocks_background;
    Music main_music;
    Text game_start_text;
} MainMenu;

typedef struct {
    Assets *assets;
    SDL_Renderer *renderer;
} MainMenuInitOptions;

void main_menu_init(MainMenu *menu, MainMenuInitOptions options);
void main_menu_quit(MainMenu *menu);
void main_menu_process_events(MainMenu *menu, SDL_Event *event);
void main_menu_render(MainMenu *menu, SDL_Renderer *renderer);

#endif // MAIN_MENU
