#include "texture.h"
#include "SDL_rect.h"
#include "SDL_render.h"

#include <SDL_image.h>

Texture texture_load(SDL_Renderer *renderer, const char *file_path)
{
    Texture result = { 0 };

    SDL_Log("Loading image: %s", file_path);
    SDL_Surface *surface = IMG_Load(file_path);
    if (!surface) {
        SDL_Log("Failed to load image %s: %s", file_path, IMG_GetError());
    } else {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_Log("Failed to create texture from %s: %s", file_path,
                    SDL_GetError());
        }
        result.texture = texture;
        result.region = (SDL_Rect){ 0, 0, surface->w, surface->h };
        SDL_FreeSurface(surface);
    }

    return result;
}

void texture_destroy(Texture *texture)
{
    if (texture->texture) {
        SDL_DestroyTexture(texture->texture);
        *texture = (Texture){ 0 };
    }
}

void texture_render(const Texture *texture, SDL_Renderer *renderer,
                    SDL_Point position)
{
    SDL_Texture *tex = texture->texture;
    SDL_Rect rect = { position.x, position.y, texture->region.w,
                      texture->region.h };

    if (!tex) {
        SDL_Log("Cannot render null texture");
        return;
    }

    if (SDL_RectEmpty(&rect)) {
        SDL_Log("Invalid texture dimensions: %dx%d", rect.w, rect.h);
        return;
    }

    bool err = SDL_RenderCopy(renderer, tex, &texture->region, &rect) < 0;
    if (err) {
        SDL_Log("Failed to render texture: %s", SDL_GetError());
    }
}
