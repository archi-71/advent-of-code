import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class Day3 {

    public static void main(String[] args) throws FileNotFoundException{
        Day3 solution = new Day3();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        int total = 0;
        while (input.hasNextLine()) {
            String data = input.nextLine();
            ArrayList<Character> firstHalf = new ArrayList<Character>();
            for (int i = 0; i < data.length()/2; i++) {
                firstHalf.add(data.charAt(i));
            }
            for (int i = data.length()/2; i < data.length(); i++) {
                if (firstHalf.contains(data.charAt(i))) {
                    total += getPriority(data.charAt(i));
                    break;
                }
            }
        }
        return total;
    }

    public int part2(Scanner input) {
        int total = 0;
        while (input.hasNextLine()) {
            String data1 = input.nextLine();
            String data2 = input.nextLine();
            String data3 = input.nextLine();
            ArrayList<Character> first = new ArrayList<Character>();
            ArrayList<Character> firstAndSecond = new ArrayList<Character>();
            for (int i = 0; i < data1.length(); i++) {
                first.add(data1.charAt(i));
            }
            for (int i = 0; i < data2.length(); i++) {
                if (first.contains(data2.charAt(i)))
                    firstAndSecond.add(data2.charAt(i));
            }
            for (int i = 0; i < data3.length(); i++) {
                if (firstAndSecond.contains(data3.charAt(i))) {
                    total += getPriority(data3.charAt(i));
                    break;
                }
            }
        }
        return total;
    }

    public int getPriority(char c) {
        int code = c;
        if (code >= 97)
            return code - 96;
        else
            return code - 38;
    }
}