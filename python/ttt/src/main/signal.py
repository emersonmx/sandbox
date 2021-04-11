from enum import IntEnum

import pygame.event
import pygame.time


class Signal(IntEnum):
    RESET = pygame.event.custom_type()
    GAMEOVER = pygame.event.custom_type()


def emit(signal: Signal) -> None:
    event = pygame.event.Event(signal)
    pygame.event.post(event)


def emit_after(signal: Signal, milliseconds: int, once: bool = True) -> None:
    event = pygame.event.Event(signal)
    pygame.time.set_timer(event, milliseconds, once)


def remove(signal: Signal) -> None:
    pygame.event.clear(signal)
    pygame.time.set_timer(signal, 0)
