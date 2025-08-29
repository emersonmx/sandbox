#include "texture.h"

#include <SDL_image.h>

Texture texture_from_file(SDL_Renderer *renderer, const char *file_path)
{
    SDL_Log("Loading image: %s", file_path);

    SDL_Surface *surface = IMG_Load(file_path);
    if (!surface) {
        SDL_Log("Failed to load image %s: %s", file_path, IMG_GetError());
        return (Texture){ 0 };
    }

    Texture texture = texture_from_surface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

Texture texture_from_surface(SDL_Renderer *renderer, SDL_Surface *surface)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return (Texture){ 0 };
    }

    return (Texture){ .texture = texture,
                      .region = { 0, 0, surface->w, surface->h } };
}

void texture_destroy(Texture *texture)
{
    if (texture->texture) {
        SDL_DestroyTexture(texture->texture);
        *texture = (Texture){ 0 };
    }
}

void texture_render(Texture *texture, SDL_Renderer *renderer,
                    SDL_Point position)
{
    SDL_Texture *sdl_texture = texture->texture;
    SDL_Rect rect = { position.x, position.y, texture->region.w,
                      texture->region.h };

    if (!sdl_texture) {
        SDL_Log("Cannot render null texture");
        return;
    }

    if (SDL_RectEmpty(&rect)) {
        SDL_Log("Invalid texture dimensions: %dx%d", rect.w, rect.h);
        return;
    }

    bool err =
        SDL_RenderCopy(renderer, sdl_texture, &texture->region, &rect) < 0;
    if (err) {
        SDL_Log("Failed to render texture: %s", SDL_GetError());
    }
}
