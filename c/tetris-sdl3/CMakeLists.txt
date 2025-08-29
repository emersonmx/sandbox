cmake_minimum_required(VERSION 4.0)

project(
    tetris-sdl3
    VERSION 0.1.0
    LANGUAGES C)

set(CMAKE_C_STANDARD 23)


# Dependencies
include(FetchContent)
FetchContent_Declare(
    SDL2
    URL https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-2.32.8.tar.gz
    URL_HASH SHA256=0ca83e9c9b31e18288c7ec811108e58bac1f1bb5ec6577ad386830eac51c787e
)
FetchContent_Declare(
    SDL2_image
    URL https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.8/SDL2_image-2.8.8.tar.gz
    URL_HASH SHA256=2213b56fdaff2220d0e38c8e420cbe1a83c87374190cba8c70af2156097ce30a
)
FetchContent_Declare(
    SDL2_ttf
    URL https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.24.0/SDL2_ttf-2.24.0.tar.gz
    URL_HASH SHA256=0b2bf1e7b6568adbdbc9bb924643f79d9dedafe061fa1ed687d1d9ac4e453bfd
)
FetchContent_Declare(
    SDL2_mixer
    URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-2.8.1.tar.gz
    URL_HASH SHA256=cb760211b056bfe44f4a1e180cc7cb201137e4d1572f2002cc1be728efd22660
)
FetchContent_Declare(
    unity
    URL https://github.com/ThrowTheSwitch/Unity/archive/refs/tags/v2.6.1.tar.gz
    URL_HASH SHA256=b41a66d45a6b99758fb3202ace6178177014d52fc524bf1f72687d93e9867292
)
FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_ttf SDL2_mixer unity)


# Application
add_executable(tetris-sdl3)
target_sources(tetris-sdl3
    PRIVATE
        assets.c
        game.c
        main.c
        main_menu.c
        mini_blocks.c
        music.c
        sound.c
        sprite.c
        text.c
        texture.c
)
target_link_libraries(tetris-sdl3
    PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
)


# Tests
include(CTest)

add_executable(example_test)
target_sources(example_test PRIVATE example_test.c)
target_include_directories(example_test PRIVATE ${unity_SOURCE_DIR}/src)
target_link_libraries(example_test unity)
add_test(example_test example_test)
