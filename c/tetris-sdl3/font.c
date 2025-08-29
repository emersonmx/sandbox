#include "resources.h"

Font font_from_file(const char *file_path, int font_size)
{
    SDL_Log("Loading font: %s", file_path);

    TTF_Font *font = TTF_OpenFont(file_path, font_size);
    if (!font) {
        SDL_Log("Failed to load font %s: %s", file_path, TTF_GetError());
    }

    return (Font){
        .ttf_font = font,
    };
}

void font_destroy(Font *font)
{
    if (font->ttf_font) {
        TTF_CloseFont(font->ttf_font);
        *font = (Font){ 0 };
    }
}
