use std::hash::{Hash, Hasher};

#[derive(Debug, Clone)]
pub struct Player {
    id: String,
    pub name: String,
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
    pub fn new(id: &str, name: &str) -> Self {
        Self {
            id: id.to_string(),
            name: name.to_string(),
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
        let player = Player::new("p1", "John");
        assert_eq!("p1", player.id());
        assert_eq!("John", player.name);
    }

    #[test]
    fn it_can_updates_the_mark() {
        let player = Player::new("p1", "John");
        assert_eq!("p1", player.id());
        assert_eq!("John", player.name);
    }
}
