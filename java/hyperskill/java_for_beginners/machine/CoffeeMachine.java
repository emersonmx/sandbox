package machine;

import java.util.Scanner;

public class CoffeeMachine {
    public static final int water = 200;
    public static final int milk = 50;
    public static final int coffee = 15;

    public static void main(String[] args) {
        int maxWater = getInput("Write how many ml of water the coffee machine has:");
        int maxMilk = getInput("Write how many ml of milk the coffee machine has:");
        int maxCoffee = getInput("Write how many grams of coffee beans the coffee machine has:");
        int cups = getInput("Write how many cups of coffee you will need:");

        int maxCups = getMaxCups(maxWater, maxMilk, maxCoffee);

        if (cups == maxCups) {
            System.out.println("Yes, I can make that amount of coffee");
        } else if (cups < maxCups) {
            System.out.println(
                    "Yes, I can make that amount of coffee (and even %d more than that)".formatted(maxCups - cups));
        } else {
            System.out.println("No, I can make only %d cup(s) of coffee".formatted(maxCups));
        }

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

    public static int getInput(String message) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(message);
        return scanner.nextInt();
    }

    public static int getMaxCups(int maxWater, int maxMilk, int maxCoffee) {
        int cups = 1;
        while (true) {
            int waterUsed = water * cups;
            int milkUsed = milk * cups;
            int coffeeUsed = coffee * cups;
            if (waterUsed <= maxWater && milkUsed <= maxMilk && coffeeUsed <= maxCoffee) {
                cups++;
            } else {
                cups--;
                break;
            }
        }
        return cups;
    }
}
