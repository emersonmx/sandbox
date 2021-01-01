use super::{errors::MarkError, mark::Mark};

type Marks = [Mark; Board::SIZE];

#[derive(Debug, PartialEq, Hash, Clone)]
pub struct Board {
    marks: Marks,
}

impl Board {
    pub const ROWS: u8 = 3;
    pub const COLUMNS: u8 = 3;
    pub const SIZE: usize = 9;

    pub fn new() -> Self {
        Self {
            marks: [Mark::None; Self::SIZE],
        }
    }

    pub fn marks(&self) -> Marks {
        self.marks
    }

    pub fn mark(&mut self, i: u8, j: u8, mark: Mark) -> Result<(), MarkError> {
        let index: usize = Self::map_to_index(i, j)?;
        if self.has_mark(i, j) {
            Err(MarkError::NotEmpty(i, j, mark))
        } else {
            self.marks[index] = mark;
            Ok(())
        }
    }

    pub fn get_mark(&self, i: u8, j: u8) -> Result<Mark, MarkError> {
        let index: usize = Self::map_to_index(i, j)?;
        Ok(self.marks[index])
    }

    pub fn clear(&mut self) {
        self.marks = [Mark::None; Self::SIZE];
    }

    pub fn is_empty(&self) -> bool {
        self.marks.iter().all(|&m| m == Mark::None)
    }

    pub fn is_full(&self) -> bool {
        self.marks.iter().all(|&m| m != Mark::None)
    }

    fn has_mark(&self, i: u8, j: u8) -> bool {
        match self.get_mark(i, j) {
            Ok(m) => m != Mark::None,
            Err(_) => false,
        }
    }

    fn map_to_index(i: u8, j: u8) -> Result<usize, MarkError> {
        let index: usize = (i * Self::ROWS + j).into();
        if index >= Self::SIZE {
            Err(MarkError::OutOfBounds(i, j))
        } else {
            Ok(index)
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn it_creates_a_empty_board() {
        let board = Board::new();
        board
            .marks()
            .iter()
            .for_each(|&x| assert_eq!(Mark::None, x));
    }

    #[test]
    fn it_marks_the_board() {
        let mut board = Board::new();
        board.mark(1, 1, Mark::O).unwrap();
        assert_eq!(Mark::O, board.get_mark(1, 1).unwrap());
    }

    #[test]
    fn it_cant_marks_outside_the_bounds() {
        let mut board = Board::new();
        assert!(board.mark(1, 1, Mark::X).is_ok());
        assert!(board.mark(3, 3, Mark::O).is_err());
    }

    #[test]
    fn it_cant_marks_a_marked_place() {
        let mut board = Board::new();
        assert!(board.mark(1, 1, Mark::X).is_ok());
        assert!(board.mark(1, 1, Mark::X).is_err());
    }

    #[test]
    fn it_clears_the_board() {
        let mut board = Board::new();
        board.mark(1, 1, Mark::O).unwrap();
        board.mark(2, 1, Mark::X).unwrap();
        assert_eq!(Mark::O, board.get_mark(1, 1).unwrap());
        assert_eq!(Mark::X, board.get_mark(2, 1).unwrap());
        board.clear();
        board
            .marks()
            .iter()
            .for_each(|&x| assert_eq!(Mark::None, x));
    }

    #[test]
    fn it_checks_filling() {
        let mut board = Board::new();
        assert!(board.is_empty());

        for i in 0..Board::ROWS {
            for j in 0..Board::COLUMNS {
                board.mark(i, j, Mark::O).unwrap()
            }
        }

        board.marks().iter().for_each(|&x| assert_eq!(Mark::O, x));
        assert!(board.is_full());

        board.clear();
        board.mark(0, 0, Mark::O).unwrap();
        assert!(!board.is_empty());
        assert!(!board.is_full());
    }
}
