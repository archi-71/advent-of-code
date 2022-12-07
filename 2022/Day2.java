import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day2 {

    public static int[][] outcomes = {{3, 6, 0},
                                      {0, 3, 6},
                                      {6, 0, 3}};
    public static void main(String[] args) throws FileNotFoundException{
        Day2 solution = new Day2();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        int total = 0;
        while (input.hasNextLine()) {
            String data = input.nextLine();
            int opponent = charToInt(data.charAt(0));
            int player = charToInt(data.charAt(2));
            total += player + 1 + outcomes[opponent][player];
        }
        return total;
    }

    public int part2(Scanner input) {
        int total = 0;
        while (input.hasNextLine()) {
            String data = input.nextLine();
            int opponent = charToInt(data.charAt(0));
            int outcome = charToInt(data.charAt(2)) * 3;
            total += outcome;
            for (int i = 0; i < 3; i++) {
                if (outcomes[opponent][i] == outcome) {
                    total += i + 1;
                    break;
                }
            }
        }
        return total;
    }

    public int charToInt(char c) {
        switch (c) {
            case 'A':
            case 'X':
                return 0;
            case 'B':
            case 'Y':
                return 1;
            default:
                return 2;
        }
    }
}