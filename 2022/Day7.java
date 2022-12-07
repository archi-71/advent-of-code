import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;

public class Day7 {
    public static void main(String[] args) throws FileNotFoundException{
        Day7 solution = new Day7();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        HashMap<Integer, Integer> directories = new HashMap<Integer, Integer>();
        ArrayList<Integer> currentPath = new ArrayList<Integer>();
        int id = 0;
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            if (data[0].equals("$")) {
                if (data[1].equals("cd")) {
                    if (data[2].equals("..")) {
                        currentPath.remove(currentPath.size()-1);
                    }
                    else {
                        directories.put(id, 0);
                        currentPath.add(id);
                        id++;
                    }
                }
            }
            else {
                if (!data[0].equals("dir")) {
                    for (int i = 0; i < currentPath.size(); i++) {
                        directories.put(currentPath.get(i), directories.get(currentPath.get(i)) + Integer.parseInt(data[0]));
                    }
                }
            }
        }
        int total = 0;
        for (int size : directories.values()) {
            if (size <= 100000)
                total += size;
        }
        return total;
    }

    public int part2(Scanner input) {
        HashMap<Integer, Integer> directories = new HashMap<Integer, Integer>();
        ArrayList<Integer> currentPath = new ArrayList<Integer>();
        int id = 0;
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            if (data[0].equals("$")) {
                if (data[1].equals("cd")) {
                    if (data[2].equals("..")) {
                        currentPath.remove(currentPath.size()-1);
                    }
                    else {
                        directories.put(id, 0);
                        currentPath.add(id);
                        id++;
                    }
                }
            }
            else {
                if (!data[0].equals("dir")) {
                    for (int i = 0; i < currentPath.size(); i++) {
                        directories.put(currentPath.get(i), directories.get(currentPath.get(i)) + Integer.parseInt(data[0]));
                    }
                }
            }
        }
        int smallestDeletion = 2147483647;
        int minDeleteSize = directories.get(0) - 40000000;
        for (int size : directories.values()) {
            if (size >= minDeleteSize && size < smallestDeletion)
                smallestDeletion = size;
        }
        return smallestDeletion;
    }
}