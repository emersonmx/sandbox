import json
import pathlib
import random
from functools import cache
from typing import Dict, List, Tuple

import pygame
import pygame.image
import pygame.surface
import pygame.transform

from main import context
from main.config import (
    BOARD_SIZE,
    HALF_TILE_SIZE,
    QUARTER_TILE_SIZE,
    SCALE_FACTOR,
    TILE_SIZE,
    WINDOW_SIZE,
)

Position = Tuple[int, int]


hlines: List[pygame.surface.Surface] = []
vlines: List[pygame.surface.Surface] = []
crosses: List[pygame.surface.Surface] = []
noughts: List[pygame.surface.Surface] = []
pause_screen: Dict[str, pygame.surface.Surface] = {}
game_over: pygame.surface.Surface
cross_wins: pygame.surface.Surface
nought_wins: pygame.surface.Surface
no_winner: pygame.surface.Surface

board_layout: Dict[Tuple[int, int], pygame.Rect] = {}


def init() -> None:
    global pause_screen, game_over, cross_wins, nought_wins
    global no_winner, board_layoutboard_layout

    layout_offset = int(WINDOW_SIZE[0] / 3)
    for i, x in enumerate(range(0, WINDOW_SIZE[0] - 2, layout_offset), 1):
        for j, y in enumerate(range(0, WINDOW_SIZE[1] - 2, layout_offset), 1):
            rect = pygame.Rect(x, y, layout_offset, layout_offset)
            board_layout[(i, j)] = rect

    assets_path = pathlib.Path("assets")
    with open(assets_path / "spritesheet.json") as f:
        spritesheet_js = json.load(f)

    sprites = spritesheet_js["frames"]
    meta = spritesheet_js["meta"]
    spritesheet = pygame.image.load(
        assets_path / meta["image"],
    ).convert_alpha()
    sprites_size = list(
        map(lambda v: v * SCALE_FACTOR, spritesheet.get_size()),
    )
    spritesheet = pygame.transform.scale(spritesheet, sprites_size)

    def make_sprite(name: str) -> pygame.surface.Surface:
        sprite_js = sprites[name]
        frame = sprite_js["frame"]
        rect: List[int] = [frame["x"], frame["y"], frame["w"], frame["h"]]
        rect = list(map(lambda v: v * SCALE_FACTOR, rect))
        return spritesheet.subsurface(rect)

    raw_noughts = make_sprite("noughts")
    for i in range(0, raw_noughts.get_width(), TILE_SIZE):
        offset = raw_noughts.get_offset()
        nought = spritesheet.subsurface(
            (offset[0] + i, offset[1], TILE_SIZE, TILE_SIZE)
        )
        noughts.append(nought)
    raw_crosses = make_sprite("crosses")
    for i in range(0, raw_crosses.get_width(), TILE_SIZE):
        offset = raw_crosses.get_offset()
        cross = spritesheet.subsurface(
            (offset[0], TILE_SIZE, TILE_SIZE, TILE_SIZE)
        )
        crosses.append(cross)

    lines = []
    raw_lines = make_sprite("lines")
    for i in range(0, TILE_SIZE, HALF_TILE_SIZE):
        offset = raw_lines.get_offset()
        line = spritesheet.subsurface(
            (offset[0], offset[1] + i, raw_lines.get_width(), HALF_TILE_SIZE)
        )
        lines.append(line)
    for line in lines:
        hlines.append(line)
        vline = line
        vline = pygame.transform.rotate(line, 90)
        vlines.append(vline)

    game_over = make_sprite("gameover")
    cross_wins = make_sprite("cross_wins")
    nought_wins = make_sprite("nought_wins")
    no_winner = make_sprite("draw")
    pause_screen["text"] = make_sprite("pause")
    pause_screen["resume"] = make_sprite("resume")
    pause_screen["restart"] = make_sprite("restart")
    pause_screen["quit"] = make_sprite("quit")


def randomize_marks() -> None:
    get_random_cross.cache_clear()
    get_random_nought.cache_clear()


def randomize_lines() -> None:
    get_random_hline.cache_clear()
    get_random_vline.cache_clear()


@cache
def get_random_cross(_: Position) -> pygame.surface.Surface:
    return random.choice(crosses)


@cache
def get_random_nought(_: Position) -> pygame.surface.Surface:
    return random.choice(noughts)


@cache
def get_random_vline(_: Position) -> pygame.surface.Surface:
    return random.choice(vlines)


@cache
def get_random_hline(_: Position) -> pygame.surface.Surface:
    return random.choice(hlines)


def draw_cross(position: Position) -> None:
    cross = get_random_cross(position)
    draw(cross, position)


def draw_nought(position: Position) -> None:
    nought = get_random_nought(position)
    draw(nought, position)


def draw_line(position: Position) -> None:
    line = get_random_hline(position)
    draw(line, position)


def draw_board(position: Position) -> None:
    rect = pygame.Rect(*position, *BOARD_SIZE)
    offset = int(BOARD_SIZE[0] / 3)
    for i in range(offset, BOARD_SIZE[0] - 2, offset):
        line_rect = rect.copy()
        line_rect.midleft = (rect.x, rect.y + i)
        line = get_random_hline(line_rect.center)
        draw(line, line_rect.center)
    for i in range(offset, BOARD_SIZE[0] - 2, offset):
        line_rect = rect.copy()
        line_rect.midtop = (rect.x + i, rect.y)
        line = get_random_vline(line_rect.center)
        draw(line, line_rect.center)


def draw_pause(position: Position) -> None:
    global pause_screen

    surface = context.screen
    surface.fill((0, 0, 0))

    sprite = pause_screen["text"]
    rect = sprite.get_rect()
    rect.topleft = position
    rect.top = QUARTER_TILE_SIZE
    draw(sprite, rect.center)

    sprite = pause_screen["resume"]
    rect.top = rect.bottom + HALF_TILE_SIZE
    draw(sprite, rect.center)

    sprite = pause_screen["restart"]
    rect.top = rect.centery + int(QUARTER_TILE_SIZE / 2)
    draw(sprite, rect.center)

    sprite = pause_screen["quit"]
    rect.top = rect.centery + int(QUARTER_TILE_SIZE / 2)
    draw(sprite, rect.center)


def draw_game_over(
    position: Position,
    winner: str,
) -> None:
    global game_over

    surface = context.screen
    surface.fill((0, 0, 0))

    rect = game_over.get_rect()
    rect.topleft = position
    rect.top = HALF_TILE_SIZE
    draw(game_over, rect.center)

    rect.top = rect.bottom + HALF_TILE_SIZE
    offset = rect.topleft

    if winner == "X":
        draw_cross_wins(offset)
    elif winner == "O":
        draw_nought_wins(offset)
    else:
        draw_no_winner(offset)


def draw_cross_wins(
    position: Position,
) -> None:
    global cross_wins
    rect = cross_wins.get_rect()
    rect.topleft = position
    draw(cross_wins, rect.center)


def draw_nought_wins(
    position: Position,
) -> None:
    global nought_wins
    rect = nought_wins.get_rect()
    rect.topleft = position
    draw(nought_wins, rect.center)


def draw_no_winner(
    position: Position,
) -> None:
    global no_winner
    rect = no_winner.get_rect()
    rect.topleft = position
    draw(no_winner, rect.center)


def draw(
    sprite: pygame.surface.Surface,
    position: Position,
) -> None:
    surface = context.screen
    rect = sprite.get_rect().copy()
    rect.center = position
    surface.blit(sprite, rect)
