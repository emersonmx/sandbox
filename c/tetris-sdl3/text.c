#include "text.h"

void text_destroy(Text *text)
{
    texture_destroy(&text->texture);
    *text = (Text){ 0 };
}

void text_update(Text *text, SDL_Renderer *renderer)
{
    TTF_Font *font = text->font.ttf_font;
    if (!font) {
        SDL_Log("Cannot render text without a font");
        return;
    }

    SDL_Surface *surface =
        TTF_RenderText_Blended(font, text->content, text->color);
    if (!surface) {
        SDL_Log("Couldn't create text surface: %s", TTF_GetError());
        return;
    }

    texture_destroy(&text->texture);
    text->texture = texture_from_surface(renderer, surface);
    SDL_FreeSurface(surface);
}

void text_render(const Text *text, SDL_Renderer *renderer)
{
    SDL_Point position = {
        .x = text->position.x - text->offset.x,
        .y = text->position.y - text->offset.y,
    };

    texture_render(&text->texture, renderer, position);
}
