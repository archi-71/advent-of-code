import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.awt.Point;

public class Day14 {

    public char[][] grid;

    public static void main(String[] args) throws FileNotFoundException{
        Day14 solution = new Day14();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        grid = new char[1000][1000];
        while (input.hasNextLine()) {
            String[] pointStrings = input.nextLine().split(" -> ");
            Point[] points = new Point[pointStrings.length];
            for (int i = 0; i < points.length; i++) {
                String[] pointString = pointStrings[i].split(",");
                points[i] =  new Point(Integer.parseInt(pointString[0]), Integer.parseInt(pointString[1]));
            }
            int index = 1;
            Point current = points[0];
            grid[current.y][current.x] = '#';
            while (index < points.length) {
                if (points[index].x > current.x)
                    current.translate(1, 0);
                else if (points[index].x < current.x)
                    current.translate(-1, 0);
                if (points[index].y > current.y)
                    current.translate(0, 1);
                else if (points[index].y < current.y)
                    current.translate(0, -1);
                grid[current.y][current.x] = '#';
                if (current.equals(points[index]))
                    index++;
            }
        }
        
        int sand = 0;
        while (dropSand1()) {
            sand++;
        }
        return sand;
    }

    public int part2(Scanner input) {
        grid = new char[1000][1000];
        int floor = -1;
        while (input.hasNextLine()) {
            String[] pointStrings = input.nextLine().split(" -> ");
            Point[] points = new Point[pointStrings.length];
            for (int i = 0; i < points.length; i++) {
                String[] pointString = pointStrings[i].split(",");
                points[i] =  new Point(Integer.parseInt(pointString[0]), Integer.parseInt(pointString[1]));
                if (points[i].y + 2 > floor)
                    floor = points[i].y + 2;
            }
            int index = 1;
            Point current = points[0];
            grid[current.y][current.x] = '#';
            while (index < points.length) {
                if (points[index].x > current.x)
                    current.translate(1, 0);
                else if (points[index].x < current.x)
                    current.translate(-1, 0);
                if (points[index].y > current.y)
                    current.translate(0, 1);
                else if (points[index].y < current.y)
                    current.translate(0, -1);
                grid[current.y][current.x] = '#';
                if (current.equals(points[index]))
                    index++;
            }
        }
        int sand = 0;
        while (dropSand2(floor)) {
            sand++;
        }
        return sand + 1;
    }

    public boolean dropSand1() {
        Point pos = new Point(500, 0);
        while (pos.y < 999) {
            pos.translate(0, 1);
            if (grid[pos.y][pos.x] != '\u0000') {
                if (grid[pos.y][pos.x - 1] == '\u0000')
                    pos.translate(-1, 0);
                else if (grid[pos.y][pos.x + 1] == '\u0000')
                    pos.translate(1, 0);
                else {
                    grid[pos.y - 1][pos.x] = 'o';
                    return true;
                }
            }
        }
        return false;
    }

    public boolean dropSand2(int floor) {
        Point pos = new Point(500, 0);
        while (pos.y < floor - 1) {
            pos.translate(0, 1);
            if (grid[pos.y][pos.x] != '\u0000') {
                if (grid[pos.y][pos.x - 1] == '\u0000')
                    pos.translate(-1, 0);
                else if (grid[pos.y][pos.x + 1] == '\u0000')
                    pos.translate(1, 0);
                else {
                    pos.translate(0, -1);
                    grid[pos.y][pos.x] = 'o';
                    return !(pos.x == 500 && pos.y == 0);
                }
            }
        }
        grid[pos.y][pos.x] = 'o';
        return true;
    }
}