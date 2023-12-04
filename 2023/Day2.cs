class Day2
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        int total = 0;
        for (int i = 0; i < data.Length; i++)
        {
            bool possible = true;
            string[] line = data[i].Substring(7 + (i + 1).ToString().Length).Split("; ");
            foreach (string list in line)
            {
                string[] colourList = list.Split(", ");
                foreach (string countAndColour in colourList)
                {
                    string[] countAndColourList = countAndColour.Split(" ");
                    int count = int.Parse(countAndColourList[0]);
                    string colour = countAndColourList[1];
                    if (count > 12 && colour == "red" || count > 13 && colour == "green" || count > 14 && colour == "blue")
                    {
                        possible = false;
                        break;
                    }
                }
            }
            if (possible)
            {
                total += i + 1;
            }
        }
        return total;
    }

    static int Part2(string[] data)
    {
        int total = 0;
        for (int i = 0; i < data.Length; i++)
        {
            int mostReds = 0;
            int mostGreens = 0;
            int mostBlues = 0;
            string[] line = data[i].Substring(7 + (i + 1).ToString().Length).Split("; ");
            foreach (string list in line)
            {
                string[] colourList = list.Split(", ");
                foreach (string countAndColour in colourList)
                {
                    string[] countAndColourList = countAndColour.Split(" ");
                    int count = int.Parse(countAndColourList[0]);
                    string colour = countAndColourList[1];
                    switch (colour)
                    {
                        case "red":
                            mostReds = Math.Max(mostReds, count);
                            break;
                        case "green":
                            mostGreens = Math.Max(mostGreens, count);
                            break;
                        case "blue":
                            mostBlues = Math.Max(mostBlues, count);
                            break;
                    }
                }
            }
            total += mostReds * mostGreens * mostBlues;
        }
        return total;
    }
}
