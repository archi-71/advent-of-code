import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.awt.Point;
import java.util.HashSet;
import java.util.ArrayList;

public class Day15 {

    public static void main(String[] args) throws FileNotFoundException{
        Day15 solution = new Day15();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        final int row = 2000000;
        HashSet<Integer> rowPositions = new HashSet<Integer>();
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            Point sensor = new Point(Integer.parseInt(data[2].substring(2, data[2].length() - 1)), Integer.parseInt(data[3].substring(2, data[3].length() - 1)));
            Point beacon = new Point(Integer.parseInt(data[8].substring(2, data[8].length() - 1)), Integer.parseInt(data[9].substring(2)));
            int manhattanDistance = Math.abs(sensor.x - beacon.x) + Math.abs(sensor.y - beacon.y);
            if (row <= sensor.y + manhattanDistance && row >= sensor.y - manhattanDistance) {
                int width = manhattanDistance - Math.abs(sensor.y - row);
                for (int i = sensor.x - width; i < sensor.x + width + 1; i++) {
                    if (!(i == beacon.x && row == beacon.y))
                        rowPositions.add(i);
                }
            }
        }
        return rowPositions.size();
    }

    public long part2(Scanner input) {
        int min = 0;
        int max = 4000000;
        ArrayList<Point> sensorPositions = new ArrayList<Point>();
        ArrayList<Integer> sensorRadii = new ArrayList<Integer>();
        while (input.hasNextLine()) {
            String[] data = input.nextLine().split(" ");
            Point sensor = new Point(Integer.parseInt(data[2].substring(2, data[2].length() - 1)), Integer.parseInt(data[3].substring(2, data[3].length() - 1)));
            Point beacon = new Point(Integer.parseInt(data[8].substring(2, data[8].length() - 1)), Integer.parseInt(data[9].substring(2)));
            int radius = Math.abs(sensor.x - beacon.x) + Math.abs(sensor.y - beacon.y);
            sensorPositions.add(sensor);
            sensorRadii.add(radius);
        }
        int x = 3446137;
        int y = 3204480;
        while (y < max + 1) {
            boolean beacon = true;
            for (int i = 0; i < sensorPositions.size(); i++) {
                int xDisplacement = sensorPositions.get(i).x - x;
                int yDisplacement = sensorPositions.get(i).y - y;
                if (Math.abs(xDisplacement) + Math.abs(yDisplacement) <= sensorRadii.get(i)) {
                    beacon = false;
                    x += xDisplacement + sensorRadii.get(i) - Math.abs(yDisplacement) + 1;
                    break;
                }
            }

            if (beacon)
                return x * 4000000l + y;

            if (x > max) {
                x = min;
                y++;
            }
        }
        return 0;
    }
}