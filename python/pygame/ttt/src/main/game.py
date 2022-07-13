#!/usr/bin/env python

import pygame
import pygame.display
import pygame.time

from main import actions, context, renderer, sprites
from main.config import FPS, WINDOW_SIZE, WINDOW_TITLE


def main() -> None:
    pygame.init()

    context.screen = pygame.display.set_mode(WINDOW_SIZE)
    pygame.display.set_caption(WINDOW_TITLE)

    actions.init()
    sprites.init()

    clock = pygame.time.Clock()
    while context.running:
        clock.tick(FPS)
        actions.process()
        renderer.render()


if __name__ == "__main__":
    main()
