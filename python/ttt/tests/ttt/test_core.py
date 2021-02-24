from typing import List, Optional, Tuple

import pytest

from ttt import Board, Game, Mark, Player, Position


def make_player1() -> Player:
    return Player(name="Alice", mark=Mark.NOUGHT)


def make_player2() -> Player:
    return Player(name="Bob", mark=Mark.CROSS)


def make_players_and_game() -> Tuple[Player, Player, Game]:
    p1 = make_player1()
    p2 = make_player2()
    game = Game(first_player=p1, second_player=p2)
    return (p1, p2, game)


def test_position_creation() -> None:
    position = Position(1, 1)
    assert position.row == 1
    assert position.column == 1


def test_use_of_mark_as_a_string() -> None:
    assert Mark.NOUGHT == "O"
    assert Mark.CROSS == "X"
    assert Mark.EMPTY == ""
    assert Mark("O") == Mark.NOUGHT
    assert Mark("X") == Mark.CROSS
    assert Mark("") == Mark.EMPTY
    assert str(Mark.NOUGHT) == "O"
    assert str(Mark.CROSS) == "X"
    assert str(Mark.EMPTY) == ""


def test_player_creation() -> None:
    player = make_player1()
    assert player.name == "Alice"
    assert player.mark == Mark.NOUGHT


def test_an_invalid_player_creation() -> None:
    with pytest.raises(ValueError, match="name cannot be empty"):
        Player(name="", mark=Mark.NOUGHT)
    with pytest.raises(ValueError, match="mark cannot be EMPTY"):
        Player(name="Alice", mark=Mark.EMPTY)


def test_the_comparison_of_the_players() -> None:
    p1 = make_player1()
    p2 = make_player2()
    p1_copy = make_player1()

    assert p1 != p2
    assert p1 == p1_copy
    assert p1 != "invalid_type"

    assert hash(p1) != hash(p2)
    assert hash(p1) == hash(p1_copy)


def test_the_creation_of_an_empty_board() -> None:
    board = Board()
    positions = []
    for p, m in board:
        assert m == Mark.EMPTY
        assert board.is_position_empty(p)
        positions.append(p)
    assert len(positions) == Board.SIZE


def test_if_has_available_positions() -> None:
    board = Board()

    assert board.has_empty_positions()
    for i in range(1, Board.ROWS + 1):
        for j in range(1, Board.COLUMNS + 1):
            assert board.has_empty_positions()
            position = Position(i, j)
            board.mark(position, Mark.NOUGHT)

    assert not board.has_empty_positions()


def test_marking_on_the_board() -> None:
    board = Board()

    position = Position(1, 1)
    assert board.is_position_empty(position)
    board.mark(position, Mark.NOUGHT)
    assert Mark.NOUGHT == board.get_mark(position)

    position = Position(2, 2)
    assert board.is_position_empty(position)
    board.mark(position, Mark.NOUGHT)
    assert Mark.NOUGHT == board.get_mark(position)


def test_invalid_board_states() -> None:
    board = Board()

    position = Position(1, 1)
    assert board.is_position_empty(position)
    with pytest.raises(ValueError, match="mark must be a NOUGHT or a CROSS"):
        board.mark(position, Mark.EMPTY)

    invalid_positions = [
        Position(1, 0),
        Position(0, 1),
        Position(0, 0),
        Position(1, Board.COLUMNS + 1),
        Position(Board.ROWS + 1, 1),
        Position(Board.ROWS + 1, Board.COLUMNS + 1),
    ]
    for invalid_position in invalid_positions:
        with pytest.raises(ValueError, match="position is out of bounds"):
            board.is_position_empty(invalid_position)
        with pytest.raises(ValueError, match="position is out of bounds"):
            board.get_mark(invalid_position)
        with pytest.raises(ValueError, match="position is out of bounds"):
            board.mark(invalid_position, Mark.NOUGHT)


def test_the_creation_of_a_game() -> None:
    p1, _, game = make_players_and_game()
    assert game.current_player == p1
    assert game.winner is None
    assert not game.is_over()
    for _, m in game.board:
        assert m == Mark.EMPTY


def test_game_turns() -> None:
    p1, p2, game = make_players_and_game()

    assert game.current_player == p1

    position = Position(1, 1)
    game.mark_position(position)
    assert p1.mark == game.board.get_mark(position)
    assert game.current_player == p2

    position = Position(2, 2)
    game.mark_position(position)
    assert p2.mark == game.board.get_mark(position)
    assert game.current_player == p1

    position = Position(3, 3)
    game.mark_position(position)
    assert p1.mark == game.board.get_mark(position)
    assert game.current_player == p2


def test_game_mark_position() -> None:
    p1, p2, game = make_players_and_game()

    assert game.current_player == p1

    position = Position(1, 1)
    assert game.board.is_position_empty(position)
    game.mark_position(position)
    assert game.current_player == p2
    assert game.board.get_mark(position) == p1.mark

    position = Position(1, 1)
    assert not game.board.is_position_empty(position)
    game.mark_position(position)
    assert game.current_player == p2
    assert game.board.get_mark(position) == p1.mark

    position = Position(2, 2)
    assert game.board.is_position_empty(position)
    game.mark_position(position)
    assert game.current_player == p1
    assert game.board.get_mark(position) == p2.mark


def test_draw_game() -> None:
    p1, p2, game = make_players_and_game()
    positions = [
        [2, 2],
        [1, 3],
        [3, 3],
        [1, 1],
        [1, 2],
        [3, 2],
        [2, 1],
        [2, 3],
        [3, 1],
    ]

    assert game.current_player == p1
    assert game.winner is None
    assert not game.is_over()
    assert game.winner is None

    for i, position in enumerate(positions):
        assert game.current_player == p1 if i % 2 == 0 else p2
        assert game.winner is None
        game.mark_position(Position(*position))

    assert game.is_over()
    assert game.current_player == p1
    assert game.winner is None


@pytest.mark.parametrize(
    "marks,winner",
    [
        # player 1 all rows win
        #  p1    p2    p1    p2    p1    p2
        (["11", "21", "12", "22", "13", "23"], make_player1()),
        (["21", "11", "22", "12", "23", "13"], make_player1()),
        (["31", "11", "32", "12", "33", "13"], make_player1()),
        # player 1 all columns win
        #  p1    p2    p1    p2    p1    p2
        (["11", "12", "21", "22", "31", "32"], make_player1()),
        (["12", "11", "22", "21", "32", "31"], make_player1()),
        (["13", "11", "23", "21", "33", "31"], make_player1()),
        # player 1 all diagonals win
        #  p1    p2    p1    p2    p1    p2
        (["11", "21", "22", "12", "33", "13"], make_player1()),
        (["31", "21", "22", "12", "13", "32"], make_player1()),
        # player 2 all rows win
        #  p1    p2    p1    p2    p1    p2
        (["21", "11", "22", "12", "33", "13"], make_player2()),
        (["11", "21", "12", "22", "33", "23"], make_player2()),
        (["11", "31", "12", "32", "23", "33"], make_player2()),
        # player 2 all columns win
        #  p1    p2    p1    p2    p1    p2
        (["12", "11", "22", "21", "33", "31"], make_player2()),
        (["11", "12", "21", "22", "33", "32"], make_player2()),
        (["11", "13", "21", "23", "32", "33"], make_player2()),
        # player 2 all diagonals win
        #  p1    p2    p1    p2    p1    p2
        (["21", "11", "12", "22", "23", "33"], make_player2()),
        (["21", "31", "12", "22", "32", "13"], make_player2()),
        # draw
        #  p1    p2    p1    p2    p1    p2    p1    p2    p1
        (["22", "13", "33", "11", "12", "32", "21", "23", "31"], None),
    ],
)
def test_game_over(marks: List, winner: Optional[Player]) -> None:
    _, _, game = make_players_and_game()

    mapped_marks = [[int(i), int(j)] for i, j in list(marks)]
    for mark in mapped_marks:
        position = Position(*mark)
        assert game.board.is_position_empty(position)
        game.mark_position(position)

    assert game.is_over()
    assert game.winner == winner


def test_invalid_game_states() -> None:
    p1 = make_player1()
    p2 = Player(name="Bob", mark=p1.mark)

    with pytest.raises(ValueError, match="The players are the same"):
        Game(p1, p1)
    with pytest.raises(ValueError, match="The players are using the same mark"):
        Game(p1, p2)
