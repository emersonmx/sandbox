#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include "texture.h"

typedef struct {
    Texture *texture;
    SDL_Point position;
    SDL_Point offset;
} Sprite;

void sprite_render(const Sprite *sprite, SDL_Renderer *renderer);

#endif // SPRITE_H
