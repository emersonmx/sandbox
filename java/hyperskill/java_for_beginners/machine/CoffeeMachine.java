package machine;

import java.util.Scanner;

public class CoffeeMachine {
    private static int moneyAmount = 550;
    private static int waterAmount = 400;
    private static int milkAmount = 540;
    private static int coffeeAmount = 120;
    private static int cupsAmount = 9;

    public static void main(String[] args) {
        showStatistics();
        System.out.println();
        String action = getAction("Write action (buy, fill, take):");
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
            default:
                break;
        }
        System.out.println();
        showStatistics();
        // int maxWater = getInput("Write how many ml of water the coffee machine
        // has:");
        // int maxMilk = getInput("Write how many ml of milk the coffee machine has:");
        // int maxCoffee = getInput("Write how many grams of coffee beans the coffee
        // machine has:");
        // int cups = getInput("Write how many cups of coffee you will need:");

        // int maxCups = getMaxCups(maxWater, maxMilk, maxCoffee);

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

    private static String getAction(String message) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(message);
        return scanner.nextLine();
    }

    private static void buyAction() {
        int option = getInput("What do you want to buy? 1 - espresso, 2 - latte, 3 - cappuccino:");
        switch (option) {
            case 1:
                makeEspresso();
                break;
            case 2:
                makeLatte();
                break;
            case 3:
                makeCappuccino();
                break;
            default:
                break;
        }
    }

    private static int getInput(String message) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(message);
        return scanner.nextInt();
    }

    private static void makeEspresso() {
        final int water = 250;
        final int coffee = 16;
        final int price = 4;
        if (water > waterAmount && coffee > coffeeAmount) {
            return;
        }

        waterAmount -= water;
        coffeeAmount -= coffee;
        cupsAmount--;
        moneyAmount += price;
    }

    private static void makeLatte() {
        final int water = 350;
        final int milk = 75;
        final int coffee = 20;
        final int price = 7;
        if (water > waterAmount && milk > milkAmount && coffee > coffeeAmount) {
            return;
        }

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
        if (water > waterAmount && milk > milkAmount && coffee > coffeeAmount) {
            return;
        }

        waterAmount -= water;
        milkAmount -= milk;
        coffeeAmount -= coffee;
        cupsAmount--;
        moneyAmount += price;
    }

    private static void fillAction() {
        waterAmount += getInput("Write how many ml of water you want to add:");
        milkAmount += getInput("Write how many ml of milk you want to add:");
        coffeeAmount += getInput("Write how many grams of coffee beans you want to add:");
        cupsAmount += getInput("Write how many disposable cups you want to add:");
    }

    private static void takeAction() {
        System.out.println("I gave you $%d".formatted(moneyAmount));
        moneyAmount = 0;
    }

    // private static int getMaxCups(int maxWater, int maxMilk, int maxCoffee) {
    // int cups = 1;
    // while (true) {
    // int waterUsed = water * cups;
    // int milkUsed = milk * cups;
    // int coffeeUsed = coffee * cups;
    // if (waterUsed <= maxWater && milkUsed <= maxMilk && coffeeUsed <= maxCoffee)
    // {
    // cups++;
    // } else {
    // cups--;
    // break;
    // }
    // }
    // return cups;
    // }
}
