import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class Day8 {
    public static void main(String[] args) throws FileNotFoundException{
        Day8 solution = new Day8();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        ArrayList<ArrayList<Integer>> grid = getGrid(input);
        int visible = 2 * (grid.size() + grid.get(0).size() - 2);
        for (int i = 1; i < grid.size()-1; i++) {
            for (int j = 1; j < grid.get(0).size()-1; j++) {
                boolean topVisible = true;
                for (int k = 0; k < i; k++) {
                    if (grid.get(k).get(j) >= grid.get(i).get(j)) {
                        topVisible = false;
                        break;
                    }
                }
                boolean bottomVisible = true;
                for (int k = i+1; k < grid.size(); k++) {
                    if (grid.get(k).get(j) >= grid.get(i).get(j)) {
                        bottomVisible = false;
                        break;
                    }
                }
                boolean leftVisible = true;
                for (int k = 0; k < j; k++) {
                    if (grid.get(i).get(k) >= grid.get(i).get(j)) {
                        leftVisible = false;
                        break;
                    }
                }
                boolean rightVisible = true;
                for (int k = j+1; k < grid.get(0).size(); k++) {
                    if (grid.get(i).get(k) >= grid.get(i).get(j)) {
                        rightVisible = false;
                        break;
                    }
                }
                if (topVisible || bottomVisible || leftVisible || rightVisible)
                    visible++;
            }
        }

        return visible;
    }

    public int part2(Scanner input) {
        ArrayList<ArrayList<Integer>> grid = getGrid(input);
        int highestScenicScore = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.get(0).size(); j++) {
                int topScore = 0;
                for (int k = i-1; k > -1; k--) {
                    topScore++;
                    if (grid.get(k).get(j) >= grid.get(i).get(j))
                        break;
                }
                int bottomScore = 0;
                for (int k = i+1; k < grid.size(); k++) {
                    bottomScore++;
                    if (grid.get(k).get(j) >= grid.get(i).get(j))
                        break;
                }
                int leftScore = 0;
                for (int k = j-1; k > -1; k--) {
                    leftScore++;
                    if (grid.get(i).get(k) >= grid.get(i).get(j))
                        break;
                }
                int rightScore = 0;
                for (int k = j+1; k < grid.get(0).size(); k++) {
                    rightScore++;
                    if (grid.get(i).get(k) >= grid.get(i).get(j))
                        break;
                }
                int scenicScore = topScore * bottomScore * leftScore * rightScore;
                if (scenicScore > highestScenicScore)
                    highestScenicScore = scenicScore;
            }
        }

        return highestScenicScore;
    }

    public ArrayList<ArrayList<Integer>> getGrid(Scanner input) {
        ArrayList<ArrayList<Integer>> grid = new ArrayList<ArrayList<Integer>>();
        while (input.hasNextLine()) {
            ArrayList<Integer> row = new ArrayList<Integer>();
            String data = input.nextLine();
            for (int i = 0; i < data.length(); i++) {
                row.add(Character.getNumericValue(data.charAt(i)));
            }
            grid.add(row);
        }
        return grid;
    }
}