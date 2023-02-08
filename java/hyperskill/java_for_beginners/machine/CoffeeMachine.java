package machine;

import java.util.Scanner;

public class CoffeeMachine {
    private static int moneyAmount = 550;
    private static int waterAmount = 400;
    private static int milkAmount = 540;
    private static int coffeeAmount = 120;
    private static int cupsAmount = 9;
    private static boolean running = true;
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        while (running) {
            String action = getInput("Write action (buy, fill, take, remaining, exit):");
            System.out.println();
            switch (action) {
                case "buy":
                    buyAction();
                    break;
                case "fill":
                    fillAction();
                    break;
                case "take":
                    takeAction();
                    break;
                case "remaining":
                    remainingAction();
                    break;
                case "exit":
                    running = false;
                    break;
                default:
                    break;
            }
            System.out.println();
        }
        // int waterAmount = getInput("Write how many ml of water the coffee machine
        // has:");
        // int milkAmount = getInput("Write how many ml of milk the coffee machine
        // has:");
        // int coffeeAmount = getInput("Write how many grams of coffee beans the coffee
        // machine has:");
        // int cups = getInput("Write how many cups of coffee you will need:");

        // int maxCups = getMaxCups(waterAmount, milkAmount, coffeeAmount);

        // if (cups == maxCups) {
        // System.out.println("Yes, I can make that amount of coffee");
        // } else if (cups < maxCups) {
        // System.out.println(
        // "Yes, I can make that amount of coffee (and even %d more than
        // that)".formatted(maxCups - cups));
        // } else {
        // System.out.println("No, I can make only %d cup(s) of
        // coffee".formatted(maxCups));
        // }

        // System.out.println("For %d cups of coffee you will need:".formatted(drinks));
        // System.out.println("%d ml of water".formatted(waterUsed));
        // System.out.println("%d ml of milk".formatted(milkUsed));
        // System.out.println("%d g of coffee beans".formatted(coffeeUsed));

        // System.out.println("""
        // Starting to make a coffee
        // Grinding coffee beans
        // Boiling water
        // Mixing boiled water with crushed coffee beans
        // Pouring coffee into the cup
        // Pouring some milk into the cup
        // Coffee is ready!""");
    }

    private static void showStatistics() {
        System.out.println("The coffee machine has:");
        System.out.println("%d ml of water".formatted(waterAmount));
        System.out.println("%d ml of milk".formatted(milkAmount));
        System.out.println("%d g of coffee beans".formatted(coffeeAmount));
        System.out.println("%d disposable cups".formatted(cupsAmount));
        System.out.println("$%d of money".formatted(moneyAmount));
    }

    private static String getInput(String message) {
        System.out.println(message);
        return scanner.nextLine();
    }

    private static void buyAction() {
        String option = getInput("""
                What do you want to buy? \
                1 - espresso, 2 - latte, 3 - cappuccino, \
                back - to main menu:""");
        switch (option) {
            case "1":
                makeEspresso();
                break;
            case "2":
                makeLatte();
                break;
            case "3":
                makeCappuccino();
                break;
            case "back":
                break;
            default:
                break;
        }
    }

    private static void makeEspresso() {
        final int water = 250;
        final int milk = 0;
        final int coffee = 16;
        final int price = 4;

        String resource = getMissingResource(water, milk, coffee);
        if (resource != "") {
            System.out.println("Sorry, not enough %s!".formatted(resource));
            return;
        }

        System.out.println("I have enough resources, making you a coffee!");

        waterAmount -= water;
        coffeeAmount -= coffee;
        cupsAmount--;
        moneyAmount += price;
    }

    private static String getMissingResource(int water, int milk, int coffee) {
        if (water > waterAmount) {
            return "water";
        }
        if (milk > milkAmount) {
            return "milk";
        }
        if (coffee > coffeeAmount) {
            return "coffee";
        }
        if (cupsAmount <= 0) {
            System.out.println("Sorry, not enough cups!");
            return "cups";
        }
        return "";
    }

    private static void makeLatte() {
        final int water = 350;
        final int milk = 75;
        final int coffee = 20;
        final int price = 7;

        String resource = getMissingResource(water, milk, coffee);
        if (resource != "") {
            System.out.println("Sorry, not enough %s!".formatted(resource));
            return;
        }

        System.out.println("I have enough resources, making you a coffee!");

        waterAmount -= water;
        milkAmount -= milk;
        coffeeAmount -= coffee;
        cupsAmount--;
        moneyAmount += price;
    }

    private static void makeCappuccino() {
        final int water = 200;
        final int milk = 100;
        final int coffee = 12;
        final int price = 6;

        String resource = getMissingResource(water, milk, coffee);
        if (resource != "") {
            System.out.println("Sorry, not enough %s!".formatted(resource));
            return;
        }

        System.out.println("I have enough resources, making you a coffee!");

        waterAmount -= water;
        milkAmount -= milk;
        coffeeAmount -= coffee;
        cupsAmount--;
        moneyAmount += price;
    }

    private static void fillAction() {
        waterAmount += Integer.parseInt(getInput("Write how many ml of water you want to add:"));
        milkAmount += Integer.parseInt(getInput("Write how many ml of milk you want to add:"));
        coffeeAmount += Integer.parseInt(getInput("Write how many grams of coffee beans you want to add:"));
        cupsAmount += Integer.parseInt(getInput("Write how many disposable cups you want to add:"));
    }

    private static void takeAction() {
        System.out.println("I gave you $%d".formatted(moneyAmount));
        moneyAmount = 0;
    }

    private static void remainingAction() {
        showStatistics();
    }

    // private static int getMaxCups() {
    // int cups = 1;
    // while (true) {
    // int waterUsed = water * cups;
    // int milkUsed = milk * cups;
    // int coffeeUsed = coffee * cups;
    // if (waterUsed <= waterAmount && milkUsed <= milkAmount && coffeeUsed <=
    // coffeeAmount) {
    // cups++;
    // } else {
    // cups--;
    // break;
    // }
    // }
    // return cups;
    // }
}
