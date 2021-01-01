#[derive(Debug, PartialEq, Hash, Clone, Copy)]
pub struct ScoreBoard {
    player1: u8,
    player2: u8,
}

impl ScoreBoard {
    pub fn new(player1: u8, player2: u8) -> Self {
        Self { player1, player2 }
    }

    pub fn player1(&self) -> u8 {
        self.player1
    }

    pub fn player2(&self) -> u8 {
        self.player2
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn it_creates_a_score_board() {
        let score_board = ScoreBoard::new(1, 2);
        assert_eq!(1, score_board.player1());
        assert_eq!(2, score_board.player2());
    }
}
