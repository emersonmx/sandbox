#ifndef MACROS_H
#define MACROS_H

#define LOAD_IMAGE(R, A, F)                                                    \
    do {                                                                       \
        SDL_Log("Loading image: %s", F);                                       \
        SDL_Surface *surface = IMG_Load(F);                                    \
        if (!surface) {                                                        \
            SDL_Log("Failed to load image %s: %s", F, IMG_GetError());         \
            A = NULL;                                                          \
        } else {                                                               \
            A = SDL_CreateTextureFromSurface(R, surface);                      \
            if (!A) {                                                          \
                SDL_Log("Failed to create texture from %s: %s", F,             \
                        SDL_GetError());                                       \
            }                                                                  \
            SDL_FreeSurface(surface);                                          \
        }                                                                      \
    } while (0);

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

#define FREE_IMAGE(A)                                                          \
    if (A) {                                                                   \
        SDL_DestroyTexture(A);                                                 \
        A = NULL;                                                              \
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
