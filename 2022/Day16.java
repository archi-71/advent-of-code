import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Queue;
import java.util.LinkedList;
import java.util.Set;
import java.util.HashSet;
import java.awt.Point;
import java.util.Arrays;
import java.util.HashMap;

public class Day16 {
    public static void main(String[] args) throws FileNotFoundException{
        Day16 solution = new Day16();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        HashMap<String, Integer> flowRates = new HashMap<String, Integer>();
        HashMap<String, String[]> connections = new HashMap<String, String[]>();
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            String name = data[1];
            int flowRate = Integer.parseInt(data[4].substring(5, data[4].length() - 1));
            flowRates.put(name, flowRate);
            ArrayList<String> tunnels = new ArrayList<String>();
            for (int i = 9; i < data.length - 1; i++) {
                tunnels.add(data[i].substring(0, data[i].length() - 1));
            }
            tunnels.add(data[data.length - 1]);
            connections.put(name, tunnels.toArray(String[]::new));
        }
        return 0;
    }

    public int part2(Scanner input) {
        return 0;
    }

    public int shortestPath(char[][] grid, Point start, Point end) {
        Queue<ArrayList<Point>> frontier = new LinkedList<ArrayList<Point>>();
        Set<Point> visited = new HashSet<Point>();
        ArrayList<Point> currentPath;
        Point currentNode;
        frontier.add(new ArrayList<Point>(Arrays.asList(start)));
        while (frontier.size() > 0) {
            currentPath = frontier.remove();
            currentNode = currentPath.get(currentPath.size() - 1);
            if (visited.contains(currentNode))
                continue;
            if (currentNode.equals(end)) {
                return currentPath.size() - 1;
            }
            visited.add(currentNode);
            for (int i = -1; i < 2; i += 2) {
                if (currentNode.y + i >= 0 && currentNode.y + i < grid.length && (int)grid[currentNode.y + i][currentNode.x] <= (int)grid[currentNode.y][currentNode.x] + 1) {
                    ArrayList<Point> newPath = new ArrayList<Point>(currentPath);
                    newPath.add(new Point(currentNode.x, currentNode.y + i));
                    frontier.add(newPath);
                }
            }
            for (int i = -1; i < 2; i += 2) {
                if (currentNode.x + i >= 0 && currentNode.x + i < grid[0].length && (int)grid[currentNode.y][currentNode.x + i] <= (int)grid[currentNode.y][currentNode.x] + 1) {
                    ArrayList<Point> newPath = new ArrayList<Point>(currentPath);
                    newPath.add(new Point(currentNode.x + i, currentNode.y));
                    frontier.add(newPath);
                }
            }
        }
        return -1;
    }
}