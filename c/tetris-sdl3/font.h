#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

typedef struct {
    TTF_Font *ttf_font;
} Font;

Font font_from_file(const char *file_path, int font_size);
void font_destroy(Font *font);

#endif // FONT_H
