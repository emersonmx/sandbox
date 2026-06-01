from enum import Enum
from typing import Literal


class Player(Enum):
    CROSS = "X"
    NOUGHT = "O"


Value = Literal[1, 2, 3]
Position = tuple[Value, Value]
Board = list[Player | None]


class FieldAlreadyTakenError(Exception):
    def __init__(
        self,
        position: Position,
        player: Player,
    ) -> None:
        self.position = position
        self.player = player
        super().__init__(
            f"Field at {self.position} has already been "
            f"taken over by player {self.player}.",
        )


class Game:
    def __init__(self, start_player: Player) -> None:
        self._board: Board = [None] * 9
        self._current_player = start_player

    def mark_field(self, i: Value, j: Value) -> None:
        index = to_index(i, j)
        if self._board[index] is None:
            self._board[index] = self._current_player
            self._take_turns_player()
        else:
            next_player = get_next_player(self._current_player)
            raise FieldAlreadyTakenError((i, j), next_player)

    def is_over(self) -> bool:
        if self._all_fields_are_taken():
            return True
        if self._a_line_are_taken():
            return True
        if self._a_column_are_taken():
            return True
        if self._a_diagonal_are_taken():
            return True
        return False

    def _all_fields_are_taken(self) -> bool:
        return all([f is not None for f in self._board])

    def _a_column_are_taken(self) -> bool:
        f11, f12, f13, f21, f22, f23, f31, f32, f33 = self._board
        if (f11 == f21 == f31) and (f11 is not None):
            return True
        if (f12 == f22 == f32) and (f12 is not None):
            return True
        if (f13 == f23 == f33) and (f13 is not None):
            return True
        return False

    def _a_line_are_taken(self) -> bool:
        f11, f12, f13, f21, f22, f23, f31, f32, f33 = self._board
        if (f11 == f12 == f13) and (f11 is not None):
            return True
        if (f21 == f22 == f23) and (f21 is not None):
            return True
        if (f31 == f32 == f33) and (f31 is not None):
            return True
        return False

    def _a_diagonal_are_taken(self) -> bool:
        f11, _, f13, _, f22, _, f31, _, f33 = self._board
        if (f11 == f22 == f33) and (f11 is not None):
            return True
        if (f13 == f22 == f31) and (f13 is not None):
            return True
        return False

    def _take_turns_player(self) -> None:
        self._current_player = get_next_player(self._current_player)


def to_index(i: Value, j: Value) -> int:
    return (i - 1) * 3 + (j - 1)


def get_next_player(player: Player) -> Player:
    if player == Player.CROSS:
        return Player.NOUGHT
    else:
        return Player.CROSS
