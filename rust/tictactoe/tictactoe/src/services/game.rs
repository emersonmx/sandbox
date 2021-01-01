use crate::domain::*;

use super::GameError;

#[derive(Debug, PartialEq, Hash)]
pub struct Game {
    game_match: Match,
    current_player: String,
}

impl Game {
    pub fn new(game_match: Match, current_player: &str) -> Self {
        Self {
            game_match,
            current_player: current_player.to_string(),
        }
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
        if self.players().contains(&player) {
            self.current_player = player.to_string();
            Ok(())
        } else {
            Err(GameError::InvalidPlayer(player.to_string()))
        }
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

    fn players(&self) -> [&str; 2] {
        return [
            self.game_match.player1().id(),
            self.game_match.player2().id(),
        ];
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

    #[test]
    fn it_creates_a_game() {
        let game_match = create_game_match();
        let game_match_clone = game_match.clone();
        let game = Game::new(game_match, game_match_clone.player1().id());
        assert_eq!(game_match_clone.id(), game.game_match().id());
    }

    #[test]
    fn it_manages_the_player_turn() {
        let game_match = create_game_match();
        let game_match_clone = game_match.clone();

        let mut game = Game::new(game_match, game_match_clone.player1().id());
        assert_eq!(game_match_clone.player1().id(), game.current_player());
        game.next_player();
        assert_eq!(game_match_clone.player2().id(), game.current_player());
        game.next_player();
        assert_eq!(game_match_clone.player1().id(), game.current_player());
        game.next_player();
        game.set_current_player(game_match_clone.player1().id())
            .unwrap();
        assert_eq!(game_match_clone.player1().id(), game.current_player());
    }

    #[test]
    fn it_validates_the_players_in_the_match() {
        let player3 = Player::new("p3", "Jane", Mark::X);
        let game_match = create_game_match();
        let game_match_clone = game_match.clone();

        let mut game = Game::new(game_match, game_match_clone.player1().id());
        assert!(game
            .set_current_player(game_match_clone.player1().id())
            .is_ok());
        assert!(game.set_current_player(player3.id()).is_err());

        match game.set_current_player(player3.id()) {
            Err(e) => println!("{}", e),
            Ok(_) => {}
        }
    }
}
