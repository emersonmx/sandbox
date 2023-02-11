package battleship;

import java.util.Arrays;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        Board board = new Board();

        // for (Ship.Type type : Ship.Type.values()) {
        // showBoard(board);
        // System.out.println();

        // String message = """
        // Enter the coordinates of \
        // the %s (%d cells):\n> \
        // """.formatted(type.getName(), type.getLength());
        // do {
        // String[] inputs = getInput(message).toUpperCase().split("\\s+");
        // System.out.println();
        // try {
        // Ship ship = new Ship(type, inputs[0], inputs[1]);
        // board.put(ship);
        // break;
        // } catch (IllegalArgumentException e) {
        // String m = e.getMessage().toLowerCase();
        // if (m.equals("invalid length")) {
        // System.out.println("""
        // Error! Wrong length \
        // of the %s! Try again:""".formatted(type.getName()));
        // } else if (m.equals("diagonal position")) {
        // System.out.println("Error! Wrong ship location! Try again:");
        // } else if (m.equals("unavailable position")) {
        // System.out.println("Error! You placed it too close to another one. Try
        // again:");
        // }
        // System.out.println();
        // }
        // } while (true);
        // }
        // showBoard(board);
    }

    private static String getInput(String message) {
        Scanner scanner = new Scanner(System.in);
        System.out.printf(message);
        return scanner.nextLine();
    }

    // private static void showBoard(Board board) {
    // char[][] cells = board.getCells();

    // System.out.print(" ");
    // for (int i = 1; i <= cells.length; i++) {
    // System.out.print(" " + i);
    // }
    // System.out.println();
    // for (int i = 0; i < cells.length; i++) {
    // System.out.print((char) ('A' + i) + " ");
    // for (int j = 0; j < cells[i].length; j++) {
    // System.out.print(cells[i][j] + " ");
    // }
    // System.out.println();
    // }
    // }
}

class Ship {
    enum Type {
        AIRCRAFT_CARRIER("Aircraft Carrier", 5),
        BATTLESHIP("Battleship", 4),
        SUBMARINE("Submarine", 3),
        CRUISER("Cruiser", 3),
        DESTROYER("Destroyer", 2);

        String name;
        int length;

        Type(String name, int length) {
            this.name = name;
            this.length = length;
        }

        public String getName() {
            return name;
        }

        public int getLength() {
            return length;
        }
    }

    Type type;
    Position startPosition;
    Position endPosition;

    Ship(Type type, String startPosition, String endPosition) {
        this(type, new Position(startPosition), new Position(endPosition));
    }

    Ship(Type type, Position startPosition, Position endPosition) {
        if (startPosition.isDiagonal(endPosition)) {
            throw new IllegalArgumentException("Diagonal position");
        }
        if (startPosition.calculateDistance(endPosition) != type.getLength() - 1) {
            throw new IllegalArgumentException("Invalid length");
        }

        this.type = type;
        this.startPosition = startPosition;
        this.endPosition = endPosition;
    }

    public Type getType() {
        return type;
    }

    public Position getStartPosition() {
        return startPosition;
    }

    public Position getEndPosition() {
        return endPosition;
    }

    public boolean isColliding(Ship ship) {
        Position[] lineA = Position.sort(startPosition, endPosition);
        Position[] lineB = Position.sort(ship.startPosition, ship.endPosition);
        Position a = lineA[0];
        Position b = lineA[1];
        Position c = lineB[0];
        Position d = lineB[1];

        double denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
        double numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
        double numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

        // Detect coincident lines (has a problem, read below)
        if (denominator == 0)
            return numerator1 == 0 && numerator2 == 0;

        double r = numerator1 / denominator;
        double s = numerator2 / denominator;

        return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
    }
}

class Board {
    private Ship[] ships;
    private int index;

    Board() {
        this(10, 10);
    }

    Board(int rows, int columns) {
        int count = Ship.Type.values().length;
        this.ships = new Ship[count];
        this.index = 0;
    }

    public Ship[] getShips() {
        return ships.clone();
    }

    public void put(Ship ship) {
        for (Ship s : ships) {
            if (ship.isColliding(s)) {
                throw new IllegalArgumentException("Unavailable position")
            }
        }
        if (index >= ships.length) {
            throw new IllegalArgumentException("Maximum amount of ships reached.");
        }
        ships[index++] = ship;
    }
}

class Position {
    int x;
    int y;

    Position(int x, int y) {
        this.x = x;
        this.y = y;
    }

    Position(String notation) {
        Pattern pattern = Pattern.compile("([A-Z])(\\d+)");
        Matcher match = pattern.matcher(notation);
        if (!match.matches()) {
            throw new IllegalArgumentException("Invalid position notation");
        }

        x = Integer.parseInt(match.group(2)) - 1;
        y = match.group(1).charAt(0) - 'A';
    }

    public boolean isVertical(Position other) {
        return y == other.y;
    }

    public boolean isHorizontal(Position other) {
        return x == other.x;
    }

    public boolean isDiagonal(Position other) {
        return !(isHorizontal(other) || isVertical(other));
    }

    public int calculateDistance(Position other) {
        int a = other.x - this.x;
        int b = other.y - this.y;
        return (int) Math.sqrt(a * a + b * b);
    }

    static Position[] sort(Position start, Position end) {
        if (start.y >= end.y && start.x >= end.x) {
            Position aux = start;
            aux = start;
            start = end;
            end = aux;
        }
        return new Position[] { start, end };
    }

    public String toString() {
        return "%s(%d, %d)".formatted(getClass().getSimpleName(), x, y);
    }
}
