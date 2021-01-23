use std::{error::Error, fmt};

use super::Mark;

#[derive(Debug, PartialEq, Clone, Copy)]
pub enum MarkError {
    OutOfBounds(u8, u8),
    NotEmpty(u8, u8, Mark),
}

impl fmt::Display for MarkError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let msg = match self {
            MarkError::OutOfBounds(i, j) => {
                format!("Mark at position ({}, {}) is out of bounds.", i, j)
            }
            MarkError::NotEmpty(i, j, m) => format!(
                "Mark \"{:?}\" at position ({}, {}) is not empty.",
                m, i, j,
            ),
        };

        write!(f, "{}", msg)
    }
}

impl Error for MarkError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        Some(self)
    }
}
