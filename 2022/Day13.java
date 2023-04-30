import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class Day13 {
    public static void main(String[] args) throws FileNotFoundException{
        Day13 solution = new Day13();
        System.out.println("Part 1 Answer: " + solution.part1(new Scanner(new File("input.txt"))));
        System.out.println("Part 2 Answer: " + solution.part2(new Scanner(new File("input.txt"))));
    }

    public int part1(Scanner input) {
        ArrayList<String[]> pairs = new ArrayList<String[]>();
        while (input.hasNextLine()) {
            pairs.add(new String[]{input.nextLine(), input.nextLine()});
            if (input.hasNextLine())
                input.nextLine();
        }
        int total = 0;
        for (int i = 0; i < pairs.size(); i++) {
            String[] pair = pairs.get(i);
            if (comparePackets(pair[0], pair[1]))
                total += i + 1;
        }
        return total;
    }

    public int part2(Scanner input) {
        ArrayList<String> packets = new ArrayList<String>();
        while (input.hasNextLine()) {
            String packet = input.nextLine();
            if (packet.length() > 0)
                packets.add(packet);
        }
        packets.add("[[2]]");
        packets.add("[[6]]");   
        for (int i = 0; i < packets.size(); i++) {  
            for (int j = 1; j < packets.size() - i; j++) {  
                if (!comparePackets(packets.get(j-1), packets.get(j))) {  
                    String temp = packets.get(j-1);  
                    packets.set(j-1, packets.get(j));
                    packets.set(j, temp);
                }          
            }  
        }
        return (packets.indexOf("[[2]]") + 1) * (packets.indexOf("[[6]]") + 1);
    }

    public Boolean comparePackets(String p1, String p2) {
        if (p1.charAt(0) != '[' && p2.charAt(0) != '[') {
            if (Integer.parseInt(p1) < Integer.parseInt(p2))
                return true;
            else if (Integer.parseInt(p1) > Integer.parseInt(p2))
                return false;
            else
                return null;
        }
        else if (p1.charAt(0) == '[' && p2.charAt(0) == '[') {
            String[] p1List = splitPacket(p1);
            String[] p2List = splitPacket(p2);
            for (int i = 0; i < p1List.length; i++) {
                if (i >= p2List.length)
                    return false;
                Boolean result = comparePackets(p1List[i], p2List[i]);
                if (result != null)
                    return result;
            }
            if (p1List.length < p2List.length)
                return true;
            else
                return null;
        }
        else {
            if (p1.charAt(0) != '[')
                p1 = "[" + p1 + "]";
            else
                p2 = "[" + p2 + "]";
            return comparePackets(p1, p2);
        }
    }

    public String[] splitPacket(String p) {
        if (p.equals("[]"))
            return new String[0];
        int brackets = 0;
        for (int i = 0; i < p.length(); i++) {
            if (p.charAt(i) == '[')
                brackets++;
            else if (p.charAt(i) == ']')
                brackets--;
            else if (brackets == 1 && p.charAt(i) == ',')
                p = p.substring(0, i) + ';' + p.substring(i + 1);
        }
        return p.substring(1, p.length() - 1).split(";");
    }
}