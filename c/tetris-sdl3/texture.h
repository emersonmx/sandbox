#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Texture *texture;
    SDL_Rect region;
} Texture;

Texture texture_load(SDL_Renderer *renderer, const char *file_path);
void texture_destroy(Texture *texture);
void texture_render(const Texture *texture, SDL_Renderer *renderer,
                    SDL_Point position);

#endif // TEXTURE_H
