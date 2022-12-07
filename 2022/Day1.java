import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class Day1 {
    public static void main(String[] args) throws FileNotFoundException{
        Day1 solution = new Day1();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        ArrayList<Integer> elfCalories = new ArrayList<Integer>(Arrays.asList(0));
        while (input.hasNextLine()) {
            String data = input.nextLine();
            if (data == "")
                elfCalories.add(0);
            else {
                int num = Integer.parseInt(data);
                int lastIndex = elfCalories.size() - 1;
                elfCalories.set(lastIndex, elfCalories.get(lastIndex) + num);
            }
        }
        return Collections.max(elfCalories);
    }

    public int part2(Scanner input) {
        ArrayList<Integer> elfCalories = new ArrayList<>(Arrays.asList(0));
        while (input.hasNextLine()) {
            String data = input.nextLine();
            if (data == "")
                elfCalories.add(0);
            else {
                int num = Integer.parseInt(data);
                int lastIndex = elfCalories.size() - 1;
                elfCalories.set(lastIndex, elfCalories.get(lastIndex) + num);
            }
        }
        int total = 0;
        Collections.sort(elfCalories);
        for (int i = 0; i < 3; i++) {
            total += elfCalories.get(elfCalories.size()-1-i);
        }
        return total;
    }
}