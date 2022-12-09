import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.awt.Point;
import java.util.HashSet;

public class Day9 {
    public static void main(String[] args) throws FileNotFoundException{
        Day9 solution = new Day9();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        Point head = new Point();
        Point tail = new Point();
        HashSet<Point> visited = new HashSet<Point>();
        visited.add(new Point(tail.x, tail.y));
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            char dir = data[0].charAt(0);
            int steps = Integer.parseInt(data[1]);
            for (int i = 0; i < steps; i++) {
                switch (dir) {
                    case 'U':
                        head.translate(0, 1);
                        break;
                    case 'D':
                        head.translate(0, -1);
                        break;
                    case 'R':
                        head.translate(1, 0);
                        break;
                    case 'L':
                        head.translate(-1, 0);
                        break;
                }
                if (Math.abs(head.x - tail.x) > 1 || Math.abs(head.y - tail.y) > 1) {
                    tail.translate((int) Math.signum(head.x - tail.x), (int) Math.signum(head.y - tail.y));
                    visited.add(new Point(tail.x, tail.y));
                }
            }
        }
        return visited.size();
    }

    public int part2(Scanner input) {
        Point[] knots = {new Point(), new Point(), new Point(), new Point(), new Point(), new Point(), new Point(), new Point(), new Point(), new Point()};
        HashSet<Point> visited = new HashSet<Point>();
        visited.add(new Point());
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            char dir = data[0].charAt(0);
            int steps = Integer.parseInt(data[1]);
            for (int i = 0; i < steps; i++) {
                switch (dir) {
                    case 'U':
                        knots[0].translate(0, 1);
                        break;
                    case 'D':
                        knots[0].translate(0, -1);
                        break;
                    case 'R':
                        knots[0].translate(1, 0);
                        break;
                    case 'L':
                        knots[0].translate(-1, 0);
                        break;
                }
                for (int j = 1; j < knots.length; j++) {
                    if (Math.abs(knots[j-1].x - knots[j].x) > 1 || Math.abs(knots[j-1].y - knots[j].y) > 1) {
                        knots[j].translate((int) Math.signum(knots[j-1].x - knots[j].x), (int) Math.signum(knots[j-1].y - knots[j].y));
                        if (j == knots.length - 1)
                            visited.add(new Point(knots[j].x, knots[j].y));
                    }
                }
            }
        }
        return visited.size();
    }
}