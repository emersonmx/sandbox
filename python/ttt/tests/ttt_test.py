from itertools import product

import pytest

from ttt import FieldAlreadyTakenError, Game, Player, Position, Value, to_index


def test_should_mark_a_field_with_x() -> None:
    game = Game(Player.CROSS)
    game.mark_field(2, 2)
    expected_board: list[Player | None] = [None] * 9
    expected_board[4] = Player.CROSS

    assert game._board == expected_board


def test_should_mark_a_field_with_o() -> None:
    game = Game(Player.NOUGHT)
    game.mark_field(2, 2)
    expected_board: list[Player | None] = [None] * 9
    expected_board[4] = Player.NOUGHT

    assert game._board == expected_board


@pytest.mark.parametrize(
    "x, y, player",
    [
        *[(x, y, Player.CROSS) for x, y in product([1, 2, 3], repeat=2)],
        *[(x, y, Player.NOUGHT) for x, y in product([1, 2, 3], repeat=2)],
    ],
)
def test_should_mark_field(
    x: Value,
    y: Value,
    player: Player,
) -> None:
    game = Game(player)
    game.mark_field(x, y)
    expected_board: list[Player | None] = [None] * 9
    index = to_index(x, y)
    expected_board[index] = player

    assert game._board == expected_board


def test_should_raise_error_when_field_are_taken() -> None:
    game = Game(Player.CROSS)
    game.mark_field(2, 2)
    with pytest.raises(FieldAlreadyTakenError) as excinfo:
        game.mark_field(2, 2)
    assert excinfo.value.position == (2, 2)
    assert excinfo.value.player == Player.CROSS
    assert game._current_player == Player.NOUGHT


def test_should_take_turns_between_players() -> None:
    game = Game(Player.CROSS)
    game.mark_field(2, 2)
    assert game._current_player == Player.NOUGHT


@pytest.mark.parametrize(
    "marks",
    [
        # when a line are taken
        [(1, 1), (2, 1), (1, 2), (2, 2), (1, 3)],
        [(2, 1), (3, 1), (2, 2), (3, 2), (2, 3)],
        [(3, 1), (1, 1), (3, 2), (1, 2), (3, 3)],
        # when a column are taken
        [(1, 1), (1, 2), (2, 1), (2, 2), (3, 1)],
        [(1, 2), (1, 3), (2, 2), (2, 3), (3, 2)],
        [(1, 3), (1, 1), (2, 3), (2, 1), (3, 3)],
        # when a diagonal are taken
        [(1, 1), (1, 3), (2, 2), (2, 3), (3, 3)],
        [(1, 3), (1, 1), (2, 2), (2, 1), (3, 1)],
        # when all fields are taken (draw)
        [
            (1, 1),
            (2, 2),
            (1, 2),
            (1, 3),
            (3, 1),
            (2, 1),
            (2, 3),
            (3, 2),
            (3, 3),
        ],
    ],
)
def test_should_game_over_when_conditions_are_met(
    marks: list[Position],
) -> None:
    game = Game(Player.CROSS)
    for mark in marks:
        assert not game.is_over()
        game.mark_field(*mark)

    assert game.is_over()
