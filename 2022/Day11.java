import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class Day11 {

    ArrayList<Monkey> monkeys;
    public static void main(String[] args) throws FileNotFoundException{
        Day11 solution = new Day11();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public long part1(Scanner input) {
        monkeys = new ArrayList<Monkey>();
        while (input.hasNextLine()) {
            String[] data = input.nextLine().trim().split(" ");
            if (data[0].length() > 0) {
                switch (data[0]) {
                    case "Monkey":
                        monkeys.add(new Monkey());
                        break;
                    case "Starting":
                        for (int i = 2; i < data.length; i++) {
                            Long item = Long.parseLong(data[i].replace(",", ""));
                            monkeys.get(monkeys.size() - 1).items.add(item);
                        }
                        break;
                    case "Operation:":
                        if (data[4].equals("+"))
                            monkeys.get(monkeys.size() - 1).operation = (old) -> old + Integer.parseInt(data[5]);
                        else if (data[4].equals("*")) {
                            if (data[5].equals("old"))
                                monkeys.get(monkeys.size() - 1).operation = (old) -> old * old;
                            else
                                monkeys.get(monkeys.size() - 1).operation = (old) -> old * Integer.parseInt(data[5]);
                        }
                        break;
                    case "Test:":
                        monkeys.get(monkeys.size() - 1).divTest = Integer.parseInt(data[3]);
                        break;
                    default:
                        if (data[1].equals("true:"))
                            monkeys.get(monkeys.size() - 1).trueMonkey = Integer.parseInt(data[5]);
                        else if (data[1].equals("false:"))
                            monkeys.get(monkeys.size() - 1).falseMonkey = Integer.parseInt(data[5]);
                        
                }
            }
        }
        for (int i = 0; i < 20; i++) {
            for (Monkey monkey : monkeys) {
                monkey.turn1();
            }
        }
        long first = -1;
        long second = -1;
        for (Monkey monkey : monkeys) {
            if (monkey.inspections >= first) {
                second = first;
                first = monkey.inspections;
            }
            else if (monkey.inspections >= second)
                second = monkey.inspections;
        }
        return first * second;
    }

    public long part2(Scanner input) {
        monkeys = new ArrayList<Monkey>();
        int commonDivTestMultiple = 1;
        while (input.hasNextLine()) {
            String[] data = input.nextLine().trim().split(" ");
            if (data[0].length() > 0) {
                switch (data[0]) {
                    case "Monkey":
                        monkeys.add(new Monkey());
                        break;
                    case "Starting":
                        for (int i = 2; i < data.length; i++) {
                            Long item = Long.parseLong(data[i].replace(",", ""));
                            monkeys.get(monkeys.size() - 1).items.add(item);
                        }
                        break;
                    case "Operation:":
                        if (data[4].equals("+"))
                            monkeys.get(monkeys.size() - 1).operation = (old) -> old + Integer.parseInt(data[5]);
                        else if (data[4].equals("*")) {
                            if (data[5].equals("old"))
                                monkeys.get(monkeys.size() - 1).operation = (old) -> old * old;
                            else
                                monkeys.get(monkeys.size() - 1).operation = (old) -> old * Integer.parseInt(data[5]);
                        }
                        break;
                    case "Test:":
                        monkeys.get(monkeys.size() - 1).divTest = Integer.parseInt(data[3]);
                        commonDivTestMultiple *= Integer.parseInt(data[3]);
                        break;
                    default:
                        if (data[1].equals("true:"))
                            monkeys.get(monkeys.size() - 1).trueMonkey = Integer.parseInt(data[5]);
                        else if (data[1].equals("false:"))
                            monkeys.get(monkeys.size() - 1).falseMonkey = Integer.parseInt(data[5]);
                        
                }
            }
        }
        for (int i = 0; i < 10000; i++) {
            for (Monkey monkey : monkeys) {
                monkey.turn2(commonDivTestMultiple);
            }
        }
        long first = -1;
        long second = -1;
        for (Monkey monkey : monkeys) {
            if (monkey.inspections >= first) {
                second = first;
                first = monkey.inspections;
            }
            else if (monkey.inspections >= second)
                second = monkey.inspections;
        }
        return first * second;
    }

    interface Operation {
        long worryOperation(long old);
     }

    public class Monkey {

        public ArrayList<Long> items = new ArrayList<Long>();
        public Operation operation;
        public int divTest;
        public int trueMonkey;
        public int falseMonkey;
        public long inspections = 0;

        public void turn1() {
            for (long item : items) {
                inspections++;
                item = operation.worryOperation(item) / 3;
                if (item % divTest == 0)
                    monkeys.get(trueMonkey).throwItem(item);
                else
                    monkeys.get(falseMonkey).throwItem(item);
            }
            items = new ArrayList<Long>();
        }

        public void turn2(int commonDivTestMultiple) {
            for (long item : items) {
                inspections++;
                item = operation.worryOperation(item);
                if (item % divTest == 0) {
                    monkeys.get(trueMonkey).throwItem(item % commonDivTestMultiple);
                }
                else {
                    monkeys.get(falseMonkey).throwItem(item % commonDivTestMultiple);
                }
            }
            items = new ArrayList<Long>();
        }

        public void throwItem(long item) {
            items.add(item);
        }
    }
}