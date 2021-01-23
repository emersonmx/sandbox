use super::{Mark, MarkError, Space};

type Marks = [Mark; Board::SIZE];

#[derive(Debug, PartialEq, Hash, Clone)]
pub struct Board {
    marks: Marks,
}

impl Board {
    pub const ROWS: u8 = 3;
    pub const COLUMNS: u8 = 3;
    const SIZE: usize = (Self::ROWS * Self::COLUMNS) as usize;

    pub fn new() -> Self {
        Self {
            marks: [Mark::None; Self::SIZE],
        }
    }

    pub fn marks(&self) -> Marks {
        self.marks
    }

    pub fn mark(&mut self, space: Space, mark: Mark) -> Result<(), MarkError> {
        let index = Self::map_to_index(space);
        if self.has_mark(space) {
            Err(MarkError::NotEmpty(space.row, space.column, mark))
        } else {
            self.marks[index] = mark;
            Ok(())
        }
    }

    pub fn get_mark(&self, space: Space) -> Mark {
        let index = Self::map_to_index(space);
        self.marks[index]
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

    fn has_mark(&self, space: Space) -> bool {
        self.get_mark(space) != Mark::None
    }

    fn map_to_index(space: Space) -> usize {
        let i = space.row - 1;
        let j = space.column - 1;
        (i * Self::ROWS + j).into()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn it_creates_a_empty_board() {
        let board = Board::new();
        assert!(board.is_empty());
    }

    #[test]
    fn it_marks_the_board() {
        let mut board = Board::new();
        board.mark(Space::new(1, 1), Mark::O).unwrap();
        assert_eq!(Mark::O, board.get_mark(Space::new(1, 1)));
    }

    #[test]
    fn it_cant_marks_a_marked_place() {
        let mut board = Board::new();
        assert!(board.mark(Space::new(1, 1), Mark::X).is_ok());
        assert!(board.mark(Space::new(1, 1), Mark::X).is_err());
    }

    #[test]
    fn it_clears_the_board() {
        let mut board = Board::new();
        board.mark(Space::new(1, 1), Mark::O).unwrap();
        board.mark(Space::new(2, 1), Mark::X).unwrap();
        assert_eq!(Mark::O, board.get_mark(Space::new(1, 1)));
        assert_eq!(Mark::X, board.get_mark(Space::new(2, 1)));
        board.clear();
        assert!(board.is_empty());
    }

    #[test]
    fn it_checks_filling() {
        let mut board = Board::new();
        assert!(board.is_empty());

        for i in 1..=Board::ROWS {
            for j in 1..=Board::COLUMNS {
                board.mark(Space::new(i, j), Mark::O).unwrap();
            }
        }
        assert!(board.is_full());

        board.clear();
        board.mark(Space::new(1, 1), Mark::O).unwrap();
        assert!(!board.is_empty());
        assert!(!board.is_full());
    }
}
