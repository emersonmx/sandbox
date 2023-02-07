package tictactoe;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private static char[][] board;

    public static void main(String[] args) {
        String input = getInput("> ");
        setupBoard(input);
        showBoard();
        checkPlayerInput();
        showBoard();
        // checkGameOver();
    }

    public static String getInput(String message) {
        Scanner scanner = new Scanner(System.in);
        System.out.print(message);
        return scanner.nextLine();
    }

    public static void setupBoard(String input) {
        board = new char[3][3];
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                board[i][j] = input.charAt(i * board.length + j);
            }
        }
    }

    public static void showBoard() {
        System.out.println("---------");
        for (int i = 0; i < board.length; i++) {
            System.out.print("| ");
            for (int j = 0; j < board[i].length; j++) {
                char c = board[i][j];
                System.out.print(c + " ");
            }
            System.out.println("|");
        }
        System.out.println("---------");
    }

    public static void checkPlayerInput() {
        while (true) {
            String input = getInput("> ");
            int[] inputs = toInputArray(input);
            if (inputs == null) {
                System.out.println("You should enter numbers!");
                continue;
            }

            int i = inputs[0] - 1;
            int j = inputs[1] - 1;
            if (i < 0 || i > 2 || j < 0 || j > 2) {
                System.out.println("Coordinates should be from 1 to 3!");
                continue;
            }

            if (!isEmptyCell(i, j)) {
                System.out.println("This cell is occupied! Choose another one!");
                continue;
            }

            board[i][j] = 'X';
            break;
        }
    }

    public static int[] toInputArray(String input) {
        Pattern pattern = Pattern.compile("^\\s*(\\d+)\\s+(\\d+)\\s*$");
        Matcher match = pattern.matcher(input);
        if (match.matches()) {
            return new int[] {
                    Integer.parseInt(match.group(1)),
                    Integer.parseInt(match.group(2)),
            };
        }
        return null;
    }

    public static void checkGameOver() {
        if (isImpossible()) {
            System.out.println("Impossible");
        } else if (isPlayerWon('X')) {
            System.out.println("X wins");
        } else if (isPlayerWon('O')) {
            System.out.println("O wins");
        } else if (hasEmptyCells()) {
            System.out.println("Game not finished");
        } else {
            System.out.println("Draw");
        }
    }

    public static boolean isImpossible() {
        if (isPlayerWon('X') && isPlayerWon('O')) {
            return true;
        }
        return Math.abs(countCells('X') - countCells('O')) > 1;
    }

    public static int countCells(char player) {
        int count = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                char c = board[i][j];
                if (c == player) {
                    count++;
                }
            }
        }
        return count;
    }

    public static boolean isPlayerWon(char player) {
        int[][][] nrows = {
                // Rows
                { { 0, 0 }, { 0, 1 }, { 0, 2 } },
                { { 1, 0 }, { 1, 1 }, { 1, 2 } },
                { { 2, 0 }, { 2, 1 }, { 2, 2 } },

                // Columns
                { { 0, 0 }, { 0, 1 }, { 0, 2 } },
                { { 1, 0 }, { 1, 1 }, { 1, 2 } },
                { { 2, 0 }, { 2, 1 }, { 2, 2 } },

                // Diagonals
                { { 0, 0 }, { 1, 1 }, { 2, 2 } },
                { { 0, 2 }, { 1, 1 }, { 2, 0 } },
        };

        for (int[][] row : nrows) {
            int[] a = row[0];
            int[] b = row[1];
            int[] c = row[2];
            if (checkRow(a, b, c)) {
                if (player == board[a[0]][a[1]]) {
                    return true;
                }
            }
        }
        return false;
    }

    public static boolean checkRow(int[] a, int[] b, int[] c) {
        return board[a[0]][a[1]] == board[b[0]][b[1]] && board[b[0]][b[1]] == board[c[0]][c[1]];
    }

    public static boolean hasEmptyCells() {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (isEmptyCell(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static boolean isEmptyCell(int i, int j) {
        char c = board[i][j];
        return c == ' ' || c == '_';
    }
}
