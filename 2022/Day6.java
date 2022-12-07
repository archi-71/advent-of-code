import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class Day6 {
    public static void main(String[] args) throws FileNotFoundException{
        Day6 solution = new Day6();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        String data = input.nextLine();
        for (int i = 0; i < data.length()-3; i++) {
            ArrayList<Character> marker = new ArrayList<Character>();
            for (int j = 0; j < 4; j++) {
                if (marker.contains(data.charAt(i + j)))
                    break;
                marker.add(data.charAt(i + j));
            }
            if (marker.size() == 4)
                return i + 4;
        }
        return -1;
    }

    public int part2(Scanner input) {
        String data = input.nextLine();
        for (int i = 0; i < data.length()-13; i++) {
            ArrayList<Character> marker = new ArrayList<Character>();
            for (int j = 0; j < 14; j++) {
                if (marker.contains(data.charAt(i + j)))
                    break;
                marker.add(data.charAt(i + j));
            }
            if (marker.size() == 14)
                return i + 14;
        }
        return -1;
    }
}