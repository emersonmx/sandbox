#ifndef MACROS_H
#define MACROS_H

#define LOAD_FONT(A, F, S)                                                     \
    SDL_Log("Loading font: %s", F);                                            \
    A = TTF_OpenFont(F, S);                                                    \
    if (!A) {                                                                  \
        SDL_Log("Failed to load font %s: %s", F, TTF_GetError());              \
    }

#define FREE_FONT(A)                                                           \
    if (A) {                                                                   \
        TTF_CloseFont(A);                                                      \
        A = NULL;                                                              \
    }

#endif // MACROS_H
