import java.util.*;

public class Cinema {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the number of rows:");
        System.out.print("> ");
        int rows = scanner.nextInt();
        System.out.println("Enter the number of seats in each row:");
        System.out.print("> ");
        int columns = scanner.nextInt();
        System.out.println();

        char[][] seats = new char[rows][columns];
        for (int i = 0; i < seats.length; i++) {
            Arrays.fill(seats[i], 'S');
        }

        printSeats(seats);

        System.out.println("Enter a row number:");
        System.out.print("> ");
        int row = scanner.nextInt();
        System.out.println("Enter a seat number in that row:");
        System.out.print("> ");
        int column = scanner.nextInt();

        int price = 0;
        int seatCount = rows * columns;
        if (seatCount < 60) {
            price = 10;
        } else {
            int frontHalf = rows / 2;
            if (row <= frontHalf) {
                price = 10;
            } else {
                price = 8;
            }
        }

        System.out.println();
        System.out.println("Ticket price: $" + price);
        System.out.println();

        seats[row - 1][column - 1] = 'B';
        printSeats(seats);
    }

    public static void printSeats(char[][] seats) {
        int rows = seats.length;
        int columns = seats.length > 0 ? seats[0].length : 0;

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

    }
}
