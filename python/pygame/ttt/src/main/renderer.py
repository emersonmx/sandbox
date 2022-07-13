import pygame
import pygame.display

from main import context, sprites
from ttt.domain.models import Mark


def render_board() -> None:
    sprites.draw_board((0, 0))

    for pos, mark in context.match.board:
        rect = sprites.board_layout[(pos.row, pos.column)]
        if mark == Mark.CROSS:
            sprites.draw_cross(rect.center)
        elif mark == Mark.NOUGHT:
            sprites.draw_nought(rect.center)


def render_game_over() -> None:
    if not context.match_is_over:
        return

    winner_map = {
        Mark.CROSS: "X",
        Mark.NOUGHT: "O",
        Mark.EMPTY: "",
    }
    match_winner = context.match.winner
    winner_mark = match_winner.mark if match_winner else Mark.EMPTY
    winner = winner_map[winner_mark]
    sprites.draw_game_over((0, 0), winner)


def render_pause_screen() -> None:
    if not context.can_pause:
        return
    if not context.paused:
        return

    sprites.draw_pause((0, 0))


def render() -> None:
    context.screen.fill((0, 0, 0))

    render_board()
    render_game_over()
    render_pause_screen()

    pygame.display.flip()
