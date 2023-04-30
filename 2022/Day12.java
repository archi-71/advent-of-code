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

public class Day12 {
    public static void main(String[] args) throws FileNotFoundException{
        Day12 solution = new Day12();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        ArrayList<String> data = new ArrayList<String>();
        while (input.hasNextLine()) {
            data.add(input.nextLine());
        }
        char[][] grid = new char[data.size()][data.get(0).length()];
        Point start = new Point();
        Point end = new Point();
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data.get(0).length(); j++) {
                if (data.get(i).charAt(j) == 'S') {
                    start = new Point(j, i);
                    grid[i][j] = 'a';
                }
                else if (data.get(i).charAt(j) == 'E') {
                    end = new Point(j, i);
                    grid[i][j] = 'z';
                }
                else {
                    grid[i][j] = data.get(i).charAt(j);
                }
            }
        }
        return shortestPath(grid, start, end);
    }

    public int part2(Scanner input) {
        ArrayList<String> data = new ArrayList<String>();
        while (input.hasNextLine()) {
            data.add(input.nextLine());
        }
        char[][] grid = new char[data.size()][data.get(0).length()];
        ArrayList<Point> starts = new ArrayList<Point>();
        Point end = new Point();
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data.get(0).length(); j++) {
                if (data.get(i).charAt(j) == 'S' || data.get(i).charAt(j) == 'a') {
                    starts.add(new Point(j, i));
                    grid[i][j] = 'a';
                }
                else if (data.get(i).charAt(j) == 'E') {
                    end = new Point(j, i);
                    grid[i][j] = 'z';
                }
                else {
                    grid[i][j] = data.get(i).charAt(j);
                }
            }
        }
        int fewestSteps = Integer.MAX_VALUE;
        for (Point start : starts) {
            int steps = shortestPath(grid, start, end);
            if (steps != -1 && steps < fewestSteps)
                fewestSteps = steps;
        }
        return fewestSteps;
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