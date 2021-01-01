use std::{error::Error, fmt};

#[derive(Debug, PartialEq, Clone)]
pub enum GameError {
    InvalidPlayer(String),
}

impl Error for GameError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        Some(self)
    }
}

impl fmt::Display for GameError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let msg = match self {
            GameError::InvalidPlayer(id) => {
                format!("The player {} is not part of the game.", id)
            }
        };

        write!(f, "{}", msg)
    }
}
