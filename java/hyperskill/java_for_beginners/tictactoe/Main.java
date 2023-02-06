package tictactoe;

import java.util.Scanner;

public class Main {
    private static final int ROWS = 3;
    private static final int COLUMNS = 3;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("> ");
        String board = scanner.nextLine().substring(0, 9);

        System.out.println("---------");
        for (int i = 0; i < ROWS; i++) {
            System.out.print("| ");
            for (int j = 0; j < COLUMNS; j++) {
                char c = board.charAt(i * COLUMNS + j);
                System.out.print(c + " ");
            }
            System.out.println("|");
        }
        System.out.println("---------");
    }
}
