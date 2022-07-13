from dataclasses import dataclass
from enum import Enum
from typing import Iterable, Iterator, List, Optional, Tuple


@dataclass(frozen=True, repr=True)
class Position:
    row: int
    column: int


class Mark(str, Enum):
    EMPTY = ""
    NOUGHT = "O"
    CROSS = "X"

    def __str__(self) -> str:
        return self.value


@dataclass(frozen=True, repr=True)
class Player:
    mark: Mark

    def __post_init__(self) -> None:
        if self.mark not in [Mark.NOUGHT, Mark.CROSS]:
            raise ValueError("mark cannot be EMPTY")


class Board(Iterable):
    ROWS = 3
    COLUMNS = 3
    SIZE = ROWS * COLUMNS

    def __init__(self) -> None:
        self._board = [Mark.EMPTY] * self.SIZE

    def is_position_empty(self, position: Position) -> bool:
        return self.get_mark(position) == Mark.EMPTY

    def has_empty_positions(self) -> bool:
        for mark in self._board:
            if mark == Mark.EMPTY:
                return True
        return False

    def get_mark(self, position: Position) -> Mark:
        idx = self._get_index(position)
        return self._board[idx]

    def mark(self, position: Position, mark: Mark) -> None:
        if mark not in [Mark.NOUGHT, Mark.CROSS]:
            raise ValueError("mark must be a NOUGHT or a CROSS")
        idx = self._get_index(position)
        self._board[idx] = mark

    def _get_index(self, position: Position) -> int:
        if position.row < 1 or position.row > Board.ROWS:
            raise ValueError("position is out of bounds")
        if position.column < 1 or position.column > Board.ROWS:
            raise ValueError("position is out of bounds")

        i = position.row - 1
        j = position.column - 1
        return i * self.ROWS + j

    def __iter__(self) -> Iterator[Tuple[Position, Mark]]:
        for i in range(1, self.ROWS + 1):
            for j in range(1, self.COLUMNS + 1):
                position = Position(i, j)
                yield (position, self.get_mark(position))


class Match:
    def __init__(self, first_player: Player, second_player: Player):
        if first_player.mark == second_player.mark:
            raise ValueError("The players are using the same mark")

        self._current_player = first_player
        self._first_player = first_player
        self._second_player = second_player
        self._board = Board()
        self._winner: Optional[Player] = None

    @property
    def current_player(self) -> Player:
        return self._current_player

    @property
    def board(self) -> Board:
        return self._board

    @property
    def winner(self) -> Optional[Player]:
        return self._winner

    def is_over(self) -> bool:
        self._winner = self.current_player
        if self._has_winner_by_rows():
            return True
        if self._has_winner_by_columns():
            return True
        if self._has_winner_by_diagonals():
            return True

        self._winner = None
        if not self._board.has_empty_positions():
            return True

        return False

    def _has_a_winner_line_for_mark(
        self,
        line: List[Position],
        mark: Mark,
    ) -> bool:
        return all([mark == self._board.get_mark(p) for p in line])

    def _has_winner_for_line(self, line: List[Position]) -> bool:
        if self._has_a_winner_line_for_mark(
            line,
            Mark.NOUGHT,
        ):
            return True
        if self._has_a_winner_line_for_mark(
            line,
            Mark.CROSS,
        ):
            return True
        return False

    def _has_winner_by_rows(self) -> bool:
        for r in range(1, Board.ROWS + 1):
            row = [Position(r, c) for c in range(1, Board.COLUMNS + 1)]
            if self._has_winner_for_line(row):
                return True
        return False

    def _has_winner_by_columns(self) -> bool:
        for c in range(1, Board.COLUMNS + 1):
            column = [Position(r, c) for r in range(1, Board.ROWS + 1)]
            if self._has_winner_for_line(column):
                return True
        return False

    def _has_winner_by_diagonals(self) -> bool:
        rows = Board.ROWS
        main_diagonal = [Position(i, i) for i in range(1, rows + 1)]
        if self._has_winner_for_line(main_diagonal):
            return True

        anti_diagonal = [
            Position(i, (rows + 1) - i) for i in range(1, rows + 1)
        ]
        if self._has_winner_for_line(anti_diagonal):
            return True

        return False

    def mark_position(self, position: Position) -> None:
        if not self._board.is_position_empty(position):
            return
        self._board.mark(position, self.current_player.mark)
        self._next_player()

    def _next_player(self) -> None:
        if self.is_over():
            return
        if self._current_player == self._first_player:
            self._current_player = self._second_player
        else:
            self._current_player = self._first_player
