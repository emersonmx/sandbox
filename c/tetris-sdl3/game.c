#include "game.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "assets.h"
#include "config.h"
#include "main_menu.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    Assets assets;

    MainMenu main_menu;
} Game;

static GameResult init(Game *game, int argc, char *argv[])
{
    bool err = SDL_Init(SDL_INIT_EVERYTHING) < 0;
    if (err) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return GAME_FAILURE;
    }

    err = SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                      &game->window, &game->renderer) < 0;
    if (err) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return GAME_FAILURE;
    }

    SDL_SetWindowTitle(game->window, WINDOW_TITLE);
    SDL_RenderSetLogicalSize(game->renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    err = IMG_Init(IMG_INIT_PNG) < 0;
    if (err) {
        SDL_Log("Couldn't initialize IMG: %s", IMG_GetError());
        return GAME_FAILURE;
    }

    err = TTF_Init() < 0;
    if (err) {
        SDL_Log("Couldn't initialize TTF: %s", TTF_GetError());
        return GAME_FAILURE;
    }

    err = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) < 0;
    if (err) {
        SDL_Log("Couldn't initialize Mixer: %s", Mix_GetError());
        return GAME_FAILURE;
    }

    assets_load(&game->assets, game->renderer);

    main_menu_init(&game->main_menu,
                   (MainMenuInitOptions){ .assets = &game->assets,
                                          .renderer = game->renderer });

    return GAME_CONTINUE;
}

static void quit(Game *game, GameResult result)
{
    main_menu_quit(&game->main_menu);

    assets_destroy(&game->assets);

    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

static GameResult process_events(Game *game, SDL_Event *event)
{
    main_menu_process_events(&game->main_menu, event);

    if (event->type == SDL_QUIT) {
        return GAME_SUCCESS;
    }

#ifndef NDEBUG
    bool is_down = event->type == SDL_KEYDOWN;
    SDL_Keycode key = event->key.keysym.sym;
    if (is_down && key == SDLK_ESCAPE) {
        return GAME_SUCCESS;
    }
#endif

    return GAME_CONTINUE;
}

static GameResult update(Game *game)
{
    SDL_Renderer *renderer = game->renderer;

    SDL_Delay(FRAME_DELAY);

    main_menu_update(&game->main_menu);

    SDL_SetRenderDrawColor(renderer, 32, 32, 32, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    main_menu_render(&game->main_menu, renderer);

    SDL_RenderPresent(renderer);

    return GAME_CONTINUE;
}

GameResult game_run(int argc, char *argv[])
{
    Game game = { 0 };
    GameResult result = init(&game, 0, NULL);

    SDL_Event event;
    while (result == GAME_CONTINUE) {
        while (SDL_PollEvent(&event)) {
            result = process_events(&game, &event);
            if (result != GAME_CONTINUE)
                goto quit;
        }

        result = update(&game);
    }

quit:
    quit(&game, result);

    return result == GAME_SUCCESS ? 0 : 1;
}
