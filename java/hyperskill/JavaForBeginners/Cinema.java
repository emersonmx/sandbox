import java.util.*;

public class Cinema {
    public static void main(String[] args) {
        int rows = getInput("Enter the number of rows:");
        int columns = getInput("Enter the number of seats in each row:");
        System.out.println();

        char[][] seats = createSeates(rows, columns);

        boolean running = true;
        while (running) {
            int input = getInput("""
                    1. Show the seats
                    2. Buy a ticket
                    0. Exit""");
            switch (input) {
                case 1:
                    showSeats(seats, rows, columns);
                    break;
                case 2:
                    buyTicket(seats, rows, columns);
                    break;
                case 0:
                    running = false;
                    break;
            }
        }
    }

    public static char[][] createSeates(int rows, int columns) {
        char[][] seats = new char[rows][columns];
        for (int i = 0; i < seats.length; i++) {
            Arrays.fill(seats[i], 'S');
        }
        return seats;
    }

    public static int getInput(String message) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(message);
        System.out.print("> ");
        return scanner.nextInt();
    }

    public static void showSeats(char[][] seats, int rows, int columns) {
        System.out.println();
        System.out.println("Cinema:");
        for (int i = 0; i <= columns; i++) {
            if (i == 0) {
                System.out.print(" ");
            } else {
                System.out.print(" " + i);
            }
        }
        System.out.println();

        for (int i = 0; i < rows; i++) {
            System.out.print(i + 1);
            for (int j = 0; j < columns; j++) {
                System.out.print(" " + seats[i][j]);
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void buyTicket(char[][] seats, int rows, int columns) {
        int row = getInput("Enter a row number:");
        int column = getInput("Enter a seat number in that row:");
        int price = calculateTicketPrice(row, column, rows, columns);
        seats[row - 1][column - 1] = 'B';
        System.out.println();
        System.out.println("Ticket price: $" + price);
        System.out.println();
    }

    public static int calculateTicketPrice(int row, int column, int rows, int columns) {
        int seatCount = rows * columns;
        if (seatCount < 60) {
            return 10;
        }

        int frontHalf = rows / 2;
        if (row <= frontHalf) {
            return 10;
        }

        return 8;
    }
}
