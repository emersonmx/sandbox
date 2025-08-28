#include "sprite.h"

void sprite_render(const Sprite *sprite, SDL_Renderer *renderer)
{
    SDL_Point position = {
        .x = sprite->position.x - sprite->offset.x,
        .y = sprite->position.y - sprite->offset.y,
    };

    texture_render(&sprite->texture, renderer, position);
}
