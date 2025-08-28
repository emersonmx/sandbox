#ifndef MACROS_H
#define MACROS_H

#define LOAD_FONT(A, F, S)                                                     \
    SDL_Log("Loading font: %s", F);                                            \
    A = TTF_OpenFont(F, S);                                                    \
    if (!A) {                                                                  \
        SDL_Log("Failed to load font %s: %s", F, TTF_GetError());              \
    }

#define LOAD_MUSIC(A, F)                                                       \
    SDL_Log("Loading music: %s", F);                                           \
    A = Mix_LoadMUS(F);                                                        \
    if (!A) {                                                                  \
        SDL_Log("Failed to load music %s: %s", F, Mix_GetError());             \
    }

#define LOAD_SOUND(A, F)                                                       \
    SDL_Log("Loading sound: %s", F);                                           \
    A = Mix_LoadWAV(F);                                                        \
    if (!A) {                                                                  \
        SDL_Log("Failed to load sound %s: %s", F, Mix_GetError());             \
    }

#define FREE_FONT(A)                                                           \
    if (A) {                                                                   \
        TTF_CloseFont(A);                                                      \
        A = NULL;                                                              \
    }

#define FREE_MUSIC(A)                                                          \
    if (A) {                                                                   \
        Mix_FreeMusic(A);                                                      \
        A = NULL;                                                              \
    }

#define FREE_SOUND(A)                                                          \
    if (A) {                                                                   \
        Mix_FreeChunk(A);                                                      \
        A = NULL;                                                              \
    }

#endif // MACROS_H
