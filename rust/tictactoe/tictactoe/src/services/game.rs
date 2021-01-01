use crate::domain::*;

use super::GameError;

#[derive(Debug, PartialEq, Hash)]
pub struct Game {
    game_match: Match,
    current_player: String,
}

impl Game {
    pub fn new(
        game_match: Match,
        first_player: &str,
    ) -> Result<Self, GameError> {
        Self::assert_current_player(
            first_player,
            game_match.player1().id(),
            game_match.player2().id(),
        )?;

        Ok(Self {
            game_match,
            current_player: first_player.to_string(),
        })
    }

    pub fn game_match(&self) -> &Match {
        &self.game_match
    }

    pub fn current_player(&self) -> &str {
        &self.current_player
    }

    pub fn set_current_player(
        &mut self,
        player: &str,
    ) -> Result<(), GameError> {
        Self::assert_current_player(
            player,
            self.game_match.player1().id(),
            self.game_match.player2().id(),
        )?;
        self.current_player = player.to_string();
        Ok(())
    }

    pub fn next_player(&mut self) {
        let p1 = self.game_match.player1().id();
        let p2 = self.game_match.player2().id();
        if self.current_player == p1 {
            self.current_player = p2.to_string()
        } else {
            self.current_player = p1.to_string()
        }
    }

    fn assert_current_player(
        player: &str,
        player1: &str,
        player2: &str,
    ) -> Result<(), GameError> {
        let players = [player1, player2];

        if players.contains(&player) {
            Ok(())
        } else {
            Err(GameError::InvalidPlayer(player.to_string()))
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    fn create_game_match() -> Match {
        let player1 = Player::new("p1", "John", Mark::O);
        let player2 = Player::new("p2", "Jane", Mark::X);
        let board = Board::new();
        let score_board = ScoreBoard::new(0, 0);
        Match::new("m1", player1, player2, board, score_board)
    }

    fn create_game() -> Game {
        let game_match = create_game_match();
        Game::new(game_match, "p1").unwrap()
    }

    #[test]
    fn it_creates_a_game() {
        let game = create_game();
        assert_eq!("m1", game.game_match().id());
        assert_eq!("p1", game.current_player());
    }

    #[test]
    fn it_manages_the_player_turn() {
        let mut game = create_game();
        assert_eq!("p1", game.current_player());
        game.next_player();
        assert_eq!("p2", game.current_player());
        game.next_player();
        assert_eq!("p1", game.current_player());
        game.next_player();
        game.set_current_player("p1").unwrap();
        assert_eq!("p1", game.current_player());
    }

    #[test]
    fn it_validates_the_players_in_the_match() {
        let player3 = Player::new("p3", "Jane", Mark::X);
        let mut game = create_game();
        assert!(game.set_current_player("p1").is_ok());
        assert!(game.set_current_player(player3.id()).is_err());
    }
}
