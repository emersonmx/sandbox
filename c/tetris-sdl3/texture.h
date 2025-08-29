#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Texture *texture;
    SDL_Rect region;
} Texture;

Texture texture_from_file(SDL_Renderer *renderer, const char *file_path);
Texture texture_from_surface(SDL_Renderer *renderer, SDL_Surface *surface);
void texture_destroy(Texture *texture);
void texture_render(Texture *texture, SDL_Renderer *renderer,
                    SDL_Point position);

#endif // TEXTURE_H
