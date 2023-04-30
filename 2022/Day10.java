import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day10 {
    public static void main(String[] args) throws FileNotFoundException{
        Day10 solution = new Day10();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        int signalStrengthSum = 0;
        int x = 1;
        int cycle = 0;
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            if (data[0].equals("noop")) {
                cycle++;
                if ((cycle - 20) % 40 == 0)
                    signalStrengthSum += cycle * x;
            }
            else if (data[0].equals("addx")) {
                cycle++;
                if ((cycle - 20) % 40 == 0)
                    signalStrengthSum += cycle * x;
                cycle++;
                if ((cycle - 20) % 40 == 0)
                    signalStrengthSum += cycle * x;
                x += Integer.parseInt(data[1]);
            }
        }
        return signalStrengthSum;
    }

    public String part2(Scanner input) {
        String[] rows = new String[]{"", "", "", "", "", ""};
        int currentRow = 0;
        int x = 1;
        int cycle = 0;
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            if (data[0].equals("noop")) {
                rows[currentRow] = drawPixel(x, cycle, rows[currentRow]);
                cycle++;
                if (cycle % 40 == 0)
                    currentRow++;
            }
            else if (data[0].equals("addx")) {
                rows[currentRow] = drawPixel(x, cycle, rows[currentRow]);
                cycle++;
                if (cycle % 40 == 0)
                    currentRow++;
                rows[currentRow] = drawPixel(x, cycle, rows[currentRow]);
                cycle++;
                if (cycle % 40 == 0)
                    currentRow++;
                x += Integer.parseInt(data[1]);
            }
        }
        return "\n" + String.join("\n", rows);
    }

    public String drawPixel(int x, int cycle, String row) {
        if ((cycle % 40) >= x - 1 && (cycle % 40) <= x + 1) {
            row += "#";
        }
        else {
            row += ".";
        }
        return row;
    }
}