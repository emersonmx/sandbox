use std::hash::{Hash, Hasher};

use super::{board::Board, player::Player, score_board::ScoreBoard};

#[derive(Debug, Clone)]
pub struct Match {
    id: String,
    player1: Player,
    player2: Player,
    board: Board,
    score_board: ScoreBoard,
}

impl PartialEq for Match {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}

impl Hash for Match {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl Match {
    pub fn new(
        id: &str,
        player1: Player,
        player2: Player,
        board: Board,
        score_board: ScoreBoard,
    ) -> Self {
        Self {
            id: id.to_string(),
            player1,
            player2,
            board,
            score_board,
        }
    }

    pub fn id(&self) -> &str {
        &self.id
    }

    pub fn player1(&self) -> &Player {
        &self.player1
    }

    pub fn player2(&self) -> &Player {
        &self.player2
    }

    pub fn board(&self) -> &Board {
        &self.board
    }

    pub fn score_board(&self) -> &ScoreBoard {
        &self.score_board
    }
}

#[cfg(test)]
mod test {
    use crate::domain::mark::Mark;

    use super::*;

    #[test]
    fn it_creates_a_match() {
        let player1 = Player::new("p1", "John", Mark::O);
        let player2 = Player::new("p2", "Jane", Mark::X);
        let board = Board::new();
        let score_board = ScoreBoard::new(0, 0);
        let game_match =
            Match::new("m1", player1, player2, board.clone(), score_board);
        assert_eq!("m1", game_match.id());
        assert_eq!("p1", game_match.player1().id());
        assert_eq!("p2", game_match.player2().id());
        assert_eq!(board, *game_match.board());
        assert_eq!(score_board, *game_match.score_board());
    }
}
