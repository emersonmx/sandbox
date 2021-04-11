from random import shuffle
from typing import Tuple

import pygame
import pygame.event

from main import context, signal, sprites
from main.signal import Signal
from ttt.domain.models import Mark, Match, Player, Position


def resume_game() -> None:
    context.paused = False
    context.can_mark_position = True


def pause_game() -> None:
    context.paused = True
    context.can_mark_position = False


def restart_match() -> None:
    signal.remove(Signal.RESET)
    signal.remove(Signal.GAMEOVER)

    player_marks = [Mark.CROSS, Mark.NOUGHT]
    shuffle(player_marks)
    players = [Player(m) for m in player_marks]
    context.match = Match(*players)

    context.paused = False
    context.can_pause = True
    context.can_mark_position = True
    context.match_is_over = False
    sprites.randomize_marks()


def quit_game() -> None:
    context.running = False


def finish_match() -> None:
    sprites.randomize_lines()
    context.match_is_over = True
    signal.emit_after(Signal.RESET, 5000)


def mark_position(position: Tuple[int, int]) -> None:
    if not context.can_mark_position:
        return

    context.match.mark_position(Position(*position))
    context.can_pause = not context.match.is_over()
    context.can_mark_position = not context.match.is_over()

    if context.match.is_over():
        signal.emit_after(Signal.GAMEOVER, 1000)


def _process_key_event(event: pygame.event.Event) -> None:
    if event.key == pygame.K_ESCAPE:
        if context.paused:
            resume_game()
        else:
            pause_game()
    elif event.key == pygame.K_q:
        quit_game()
    elif event.key == pygame.K_r:
        signal.emit(Signal.RESET)


def _process_mouse_event(event: pygame.event.Event) -> None:
    if context.match.is_over():
        return

    for mark, area in sprites.board_layout.items():
        if area.collidepoint(event.pos) and event.button == 1:
            mark_position(mark)


def process() -> None:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            quit_game()
        elif event.type == pygame.KEYUP:
            _process_key_event(event)
        elif event.type == pygame.MOUSEBUTTONUP:
            _process_mouse_event(event)
        elif event.type == Signal.GAMEOVER:
            finish_match()
        elif event.type == Signal.RESET:
            restart_match()


def init() -> None:
    restart_match()
