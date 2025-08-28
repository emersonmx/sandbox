#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "texture.h"

typedef struct {
    TTF_Font *font;
    SDL_Color color;
    Texture texture;
    SDL_Point position;
    SDL_Point offset;
    char *content;
} Text;

void text_destroy(Text *text);
void text_update(Text *text, SDL_Renderer *renderer);
void text_render(const Text *text, SDL_Renderer *renderer);

#endif // TEXT_H
