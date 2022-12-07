import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class Day5 {
    public static void main(String[] args) throws FileNotFoundException{
        Day5 solution = new Day5();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public String part1(Scanner input) {
        ArrayList<ArrayList<Character>> stacks = new ArrayList<ArrayList<Character>>();
        while (input.hasNextLine()) {
            String dataString = input.nextLine();
            char[] data = dataString.toCharArray();
            if (data.length > 0 && data[0] == '[') {
                if (stacks.size() == 0) {
                    for (int i = 0; i < (data.length + 1) / 4; i++) {
                        stacks.add(new ArrayList<Character>());
                    }
                }
                for (int i = 0; i < (data.length + 1) / 4; i++) {
                    if (data[i * 4 + 1] != ' ' && data[i * 4 + 1] != '[' && data[i * 4 + 1] != ']') {
                        stacks.get(i).add(data[i * 4 + 1]);
                    }
                }
            }
            else if (data.length > 0 && data[0] == 'm') {
                String[] split = dataString.split(" ");
                int count = Integer.parseInt(split[1]);
                int from = Integer.parseInt(split[3])-1;
                int to = Integer.parseInt(split[5])-1;
                for (int i = 0; i < count; i++) {
                    char item = stacks.get(from).remove(0);
                    stacks.get(to).add(0, item);
                }
            }
        }
        String result = "";
        for (int i = 0; i < stacks.size(); i++) {
            result += stacks.get(i).get(0);
        }
        return result;
    }

    public String part2(Scanner input) {
        ArrayList<ArrayList<Character>> stacks = new ArrayList<ArrayList<Character>>();
        while (input.hasNextLine()) {
            String dataString = input.nextLine();
            char[] data = dataString.toCharArray();
            if (data.length > 0 && data[0] == '[') {
                if (stacks.size() == 0) {
                    for (int i = 0; i < (data.length + 1) / 4; i++) {
                        stacks.add(new ArrayList<Character>());
                    }
                }
                for (int i = 0; i < (data.length + 1) / 4; i++) {
                    if (data[i * 4 + 1] != ' ' && data[i * 4 + 1] != '[' && data[i * 4 + 1] != ']') {
                        stacks.get(i).add(data[i * 4 + 1]);
                    }
                }
            }
            else if (data.length > 0 && data[0] == 'm') {
                String[] split = dataString.split(" ");
                int count = Integer.parseInt(split[1]);
                int from = Integer.parseInt(split[3])-1;
                int to = Integer.parseInt(split[5])-1;
                for (int i = 0; i < count; i++) {
                    char item = stacks.get(from).remove(0);
                    stacks.get(to).add(i, item);
                }
            }
        }
        String result = "";
        for (int i = 0; i < stacks.size(); i++) {
            result += stacks.get(i).get(0);
        }
        return result;
    }
}