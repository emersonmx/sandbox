use super::Board;

#[derive(Debug, PartialEq, Hash, Clone, Copy)]
pub struct Space {
    pub row: u8,
    pub column: u8,
}

impl Space {
    pub fn new(row: u8, column: u8) -> Self {
        Self::check_invariants(row, column);
        Space { row, column }
    }

    fn check_invariants(row: u8, column: u8) {
        assert!(1 <= row && row <= Board::ROWS, "row is not between 1 and 3");
        assert!(
            1 <= column && column <= Board::COLUMNS,
            "column is not between 1 and 3"
        );
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_creates_valid_spaces_with_row_and_column_between_1_and_3() {
        for i in 1..=Board::ROWS {
            for j in 1..=Board::COLUMNS {
                let space = Space::new(i, j);
                assert_eq!(i, space.row);
                assert_eq!(j, space.column);
            }
        }
    }

    #[test]
    #[should_panic(expected = "row is not between 1 and 3")]
    fn it_cannot_creates_a_space_with_row_and_column_lesser_than_1() {
        Space::new(0, 0);
    }

    #[test]
    #[should_panic(expected = "column is not between 1 and 3")]
    fn it_cannot_creates_a_space_with_column_lesser_that_1() {
        Space::new(1, 0);
    }

    #[test]
    #[should_panic(expected = "row is not between 1 and 3")]
    fn it_cannot_creates_a_space_with_row_lesser_than_1() {
        Space::new(0, 1);
    }

    #[test]
    #[should_panic(expected = "row is not between 1 and 3")]
    fn it_cannot_creates_a_space_greater_than_max_rows_and_columns() {
        Space::new(Board::ROWS + 1, Board::COLUMNS + 1);
    }

    #[test]
    #[should_panic(expected = "row is not between 1 and 3")]
    fn it_cannot_creates_a_space_greater_than_max_rows() {
        Space::new(Board::ROWS + 1, 1);
    }

    #[test]
    #[should_panic(expected = "column is not between 1 and 3")]
    fn it_cannot_creates_a_space_greater_than_max_columns() {
        Space::new(1, Board::COLUMNS + 1);
    }
}
