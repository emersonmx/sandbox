use thiserror::Error;

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum Player {
    CROSS,
    NOUGHT,
}

impl Iterator for Player {
    type Item = Player;

    fn next(&mut self) -> Option<Self::Item> {
        if self == &Player::CROSS {
            Some(Player::NOUGHT)
        } else {
            Some(Player::CROSS)
        }
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub struct Position(usize, usize);

impl Position {
    pub fn new(i: usize, j: usize) -> Self {
        assert!((1..=3).contains(&i), "i must be between 1 and 3");
        assert!((1..=3).contains(&j), "j must be between 1 and 3");
        Self(i, j)
    }

    fn as_index(&self) -> usize {
        let row = self.0 - 1;
        let column = self.1 - 1;
        row * BOARD_ROWS + column
    }
}

const BOARD_ROWS: usize = 3;
const BOARD_COLUMNS: usize = 3;
const BOARD_SIZE: usize = BOARD_ROWS * BOARD_COLUMNS;
pub type Board = [Option<Player>; BOARD_SIZE];

pub struct Game {
    current_player: Player,
    board: Board,
}

impl Game {
    pub fn new(start_player: Player) -> Self {
        Self {
            current_player: start_player,
            board: Default::default(),
        }
    }

    pub fn mark_field(&mut self, position: Position) -> Result<(), FieldAlreadyTakenError> {
        let index = position.as_index();
        match self.board[index] {
            Some(_) => Err(FieldAlreadyTakenError(
                position,
                self.current_player.next().unwrap(),
            )),
            None => {
                self.board[index] = Some(self.current_player);
                self.current_player = self.current_player.next().unwrap();
                Ok(())
            }
        }
    }

    fn is_over(&self) -> bool {
        if self.all_fields_are_taken() {
            return true;
        }
        if self.a_line_are_taken() {
            return true;
        }
        if self.a_column_are_taken() {
            return true;
        }
        if self.a_diagonal_are_taken() {
            return true;
        }
        false
    }

    fn all_fields_are_taken(&self) -> bool {
        self.board.iter().all(|position| position.is_some())
    }

    fn a_line_are_taken(&self) -> bool {
        let [p11, p12, p13, p21, p22, p23, p31, p32, p33] = self.board;

        if (p11 == p12 && p12 == p13) && (p11.is_some()) {
            return true;
        }
        if (p21 == p22 && p22 == p23) && (p21.is_some()) {
            return true;
        }
        if (p31 == p32 && p32 == p33) && (p31.is_some()) {
            return true;
        }

        false
    }

    fn a_column_are_taken(&self) -> bool {
        let [p11, p12, p13, p21, p22, p23, p31, p32, p33] = self.board;
        if (p11 == p21 && p21 == p31) && (p11.is_some()) {
            return true;
        }
        if (p12 == p22 && p22 == p32) && (p12.is_some()) {
            return true;
        }
        if (p13 == p23 && p23 == p33) && (p13.is_some()) {
            return true;
        }
        false
    }

    fn a_diagonal_are_taken(&self) -> bool {
        let [p11, _, p13, _, p22, _, p31, _, p33] = self.board;
        if (p11 == p22 && p22 == p33) && (p11.is_some()) {
            return true;
        }
        if (p13 == p22 && p22 == p31) && (p13.is_some()) {
            return true;
        }
        false
    }
}

#[derive(Debug, Error, PartialEq, Eq)]
#[error("field at {0:?} has been taken over by player {1:?}")]
pub struct FieldAlreadyTakenError(Position, Player);

#[cfg(test)]
mod tests {
    use super::*;

    fn make_game() -> Game {
        Game::new(Player::CROSS)
    }

    #[test]
    fn a_game_has_two_players() {
        let p1 = Player::CROSS;
        let p2 = Player::NOUGHT;

        assert_ne!(p1, p2);
    }

    #[test]
    fn a_board_starts_with_empty_fields() {
        let game = make_game();
        let board = game.board;

        assert!(board.iter().any(|i| i.is_none()));
    }

    #[test]
    fn a_player_takes_a_field_between_one_and_three() {
        for i in 1..=3 {
            for j in 1..=3 {
                Position::new(i, j);
            }
        }
    }

    #[test]
    #[should_panic]
    fn a_player_cannot_take_a_field_off_the_board() {
        Position::new(0, 0);
    }

    #[test]
    fn a_game_starts_with_one_player() {
        let game = make_game();

        assert_eq!(game.current_player, Player::CROSS);
    }

    #[test]
    fn a_player_takes_an_empty_field() {
        let mut game = make_game();
        game.mark_field(Position::new(1, 1)).unwrap();

        let board = game.board;
        assert_eq!(board[0], Some(Player::CROSS));
    }

    #[test]
    fn the_players_take_turns_with_each_other() {
        let mut game = make_game();

        assert_eq!(game.current_player, Player::CROSS);
        game.mark_field(Position::new(1, 1)).unwrap();
        assert_eq!(game.current_player, Player::NOUGHT);
        game.mark_field(Position::new(1, 2)).unwrap();
        assert_eq!(game.current_player, Player::CROSS);
    }

    #[test]
    fn a_player_cannot_take_a_field_already_taken() {
        let mut game = make_game();
        let position = Position::new(1, 1);

        game.mark_field(position).unwrap();
        let result = game.mark_field(position);

        assert_eq!(result, Err(FieldAlreadyTakenError(position, Player::CROSS)));
    }

    #[test]
    fn the_game_ends_when_the_conditions_are_met() {
        let game_tests = [
            // when a line are taken
            vec![(1, 1), (2, 1), (1, 2), (2, 2), (1, 3)],
            vec![(2, 1), (3, 1), (2, 2), (3, 2), (2, 3)],
            vec![(3, 1), (1, 1), (3, 2), (1, 2), (3, 3)],
            // when a column are taken
            vec![(1, 1), (1, 2), (2, 1), (2, 2), (3, 1)],
            vec![(1, 2), (1, 3), (2, 2), (2, 3), (3, 2)],
            vec![(1, 3), (1, 1), (2, 3), (2, 1), (3, 3)],
            // when a diagonal are taken
            vec![(1, 1), (1, 3), (2, 2), (2, 3), (3, 3)],
            vec![(1, 3), (1, 1), (2, 2), (2, 1), (3, 1)],
            // when all fields are taken (draw)
            vec![
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
        ];
        for game_test in game_tests {
            let mut game = make_game();
            for (i, j) in game_test {
                assert!(!game.is_over());
                game.mark_field(Position::new(i, j)).unwrap();
            }
            assert!(game.is_over());
        }
    }

    // A field cannot be taken when the game is over.
}
