## Domains

- Mark: enum('', 'O', 'X')

- Player (2)
    - id: str
    - name: str
    - mark: Mark

- Board
    - marks: Mark[9]

- ScoreBoard
    - player1: u8
    - player2: u8

- Match
    - id: str
    - player1: Player
    - player2: Player
    - board: Board
    - score_board: ScoreBoard

## Service

- Game
    - turn: str
    - match: Match
