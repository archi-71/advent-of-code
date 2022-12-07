import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day4 {
    public static void main(String[] args) throws FileNotFoundException{
        Day4 solution = new Day4();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        int pairs = 0;
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(",");
            String[] first = data[0].split("-");
            String[] second = data[1].split("-");
            System.out.println(first[0] + " " + first[1] + " " + second[0] + " " + second[1]);
            if (Integer.parseInt(first[0]) >= Integer.parseInt(second[0]) && Integer.parseInt(first[1]) <= Integer.parseInt(second[1]))
                pairs++;
            else if (Integer.parseInt(second[0]) >= Integer.parseInt(first[0]) && Integer.parseInt(second[1]) <= Integer.parseInt(first[1]))
                pairs++;
        }
        return pairs;
    }

    public int part2(Scanner input) {
        int pairs = 0;
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(",");
            String[] first = data[0].split("-");
            String[] second = data[1].split("-");
            if (Integer.parseInt(first[1]) >= Integer.parseInt(second[0]) && Integer.parseInt(first[1]) <= Integer.parseInt(second[1]))
                pairs++;
            else if (Integer.parseInt(second[1]) >= Integer.parseInt(first[0]) && Integer.parseInt(second[1]) <= Integer.parseInt(first[1]))
                pairs++;
        }
        return pairs;
    }
}