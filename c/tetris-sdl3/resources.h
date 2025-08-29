#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

typedef struct {
    SDL_Texture *texture;
    SDL_Rect region;
} Texture;

typedef struct {
    TTF_Font *ttf_font;
} Font;

typedef struct {
    Mix_Music *mix_music;
} Music;

typedef struct {
    Mix_Chunk *mix_chunk;
} Sound;

typedef struct {
    Texture texture;
    SDL_Point position;
    SDL_Point offset;
} Sprite;

typedef struct {
    Font font;
    SDL_Color color;
    Texture texture;
    SDL_Point position;
    SDL_Point offset;
    char *content;
} Text;

typedef struct {
    Texture block;
    Texture mini_block;
    Texture grid;
    Texture main_menu_bg;

    Font default_font;

    Music main_music;

    Sound erase_lines_sound;
    Sound fit_tetromino_sound;
    Sound game_over_sound;
    Sound game_start_sound;
    Sound menu_open_sound;
    Sound move_tetromino_sound;
    Sound rotate_tetromino_sound;
} Assets;

Texture texture_from_file(SDL_Renderer *renderer, const char *file_path);
Texture texture_from_surface(SDL_Renderer *renderer, SDL_Surface *surface);
void texture_destroy(Texture *texture);
void texture_render(Texture *texture, SDL_Renderer *renderer,
                    SDL_Point position);

Font font_from_file(const char *file_path, int font_size);
void font_destroy(Font *font);

Music music_from_file(const char *file_path);
void music_destroy(Music *music);
void music_play(Music *music);
void music_stop();

Sound sound_from_file(const char *file_path);
void sound_destroy(Sound *sound);
void sound_play(Sound *sound);
void sound_stop(Sound *sound);

void sprite_render(Sprite *sprite, SDL_Renderer *renderer);

void text_destroy(Text *text);
void text_update(Text *text, SDL_Renderer *renderer);
void text_render(Text *text, SDL_Renderer *renderer);

void assets_load(Assets *assets, SDL_Renderer *renderer);
void assets_destroy(Assets *assets);

#endif // RESOURCES_H
