use crate::domain::*;

// use super::GameError;

#[derive(Debug, PartialEq, Hash)]
pub struct Game {
    player1: Player,
    player2: Player,
    board: Board,
    current_player: String,
    score_board: ScoreBoard,
}

impl Game {
    pub fn new(
    ) -> Self {
        Self {}
    }

    pub fn mark(space: Space) {}
}

#[cfg(test)]
mod test {
    // use super::*;

    #[test]
    fn it_creates_a_game() {
        // let game = Game::new();
        // game.create_player()
        // assert_eq!("m1", game.game_match().id());
        // assert_eq!("p1", game.current_player());
    }

    // #[test]
    // fn it_manages_the_player_turn() {
    //     let mut game = create_game();
    //     assert_eq!("p1", game.current_player());
    //     game.next_player();
    //     assert_eq!("p2", game.current_player());
    //     game.next_player();
    //     assert_eq!("p1", game.current_player());
    //     game.next_player();
    //     game.set_current_player("p1").unwrap();
    //     assert_eq!("p1", game.current_player());
    // }

    // #[test]
    // fn it_validates_the_players_in_the_match() {
    //     let player3 = Player::new("p3", "Jane", Mark::X);
    //     let mut game = create_game();
    //     assert!(game.set_current_player("p1").is_ok());
    //     assert!(game.set_current_player(player3.id()).is_err());
    // }
}
