#include "mini_blocks.h"

#include "SDL_render.h"
#include "config.h"

static const char *IMAGE = "####################################"
                           "####################################"
                           "####################################"
                           "####################################"
                           "#####     #   #     #   # ##  ######"
                           "####### ### ##### ### # # # ########"
                           "####### ###  #### ###  ## ## #######"
                           "####### ### ##### ### # # ### ######"
                           "####### ###   ### ### # # #  #######"
                           "####################################"
                           "####################################"
                           "####################################"
                           "####################################"
                           "####################################"
                           "####################################"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "###                              ###"
                           "####################################"
                           "####################################"
                           "####################################";

static const SDL_Color COLORS[] = {
    { 50, 255, 255, 255 }, { 50, 50, 255, 255 }, { 255, 123, 50, 255 },
    { 255, 255, 50, 255 }, { 99, 255, 50, 255 }, { 99, 50, 99, 255 },
    { 255, 50, 50, 255 }
};

Texture mini_blocks_create(Texture mini_block, SDL_Renderer *renderer)
{
    srand(SDL_GetTicks());

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET,
                                             WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderTarget(renderer, texture);

    int width = WINDOW_WIDTH / (TILE_SIZE / 2);
    int height = WINDOW_HEIGHT / (TILE_SIZE / 2);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char c = IMAGE[i * width + j];
            if (c == '#') {
                SDL_Point position = { .x = j * (TILE_SIZE / 2),
                                       .y = i * (TILE_SIZE / 2) };
                int color_index = rand() % (sizeof(COLORS) / sizeof(COLORS[0]));
                SDL_SetTextureColorMod(
                    mini_block.texture, COLORS[color_index].r,
                    COLORS[color_index].g, COLORS[color_index].b);
                texture_render(&mini_block, renderer, position);
            }
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    return (Texture){ .texture = texture,
                      .region = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT } };
}
