use std::hash::{Hash, Hasher};

use super::Mark;

#[derive(Debug, Clone)]
pub struct Player {
    id: String,
    pub name: String,
    pub mark: Mark,
}

impl PartialEq for Player {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}

impl Hash for Player {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl Player {
    pub fn new(id: &str, name: &str, mark: Mark) -> Self {
        Self {
            id: id.to_string(),
            name: name.to_string(),
            mark,
        }
    }

    pub fn id(&self) -> &str {
        &self.id
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn it_creates_a_player() {
        let player = Player::new("p1", "John", Mark::O);
        assert_eq!("p1", player.id());
        assert_eq!("John", player.name);
        assert_eq!(Mark::O, player.mark);
    }

    #[test]
    fn it_can_updates_the_mark() {
        let mut player = Player::new("p1", "John", Mark::O);
        assert_eq!("p1", player.id());
        assert_eq!("John", player.name);
        assert_eq!(Mark::O, player.mark);

        player.mark = Mark::X;
        assert_eq!(Mark::X, player.mark);
    }
}
