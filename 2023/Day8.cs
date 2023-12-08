class Day8
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        Dictionary<string, string[]> network = new Dictionary<string, string[]>();
        for (int i = 2; i < data.Length; i++)
        {
            network[data[i].Substring(0, 3)] = new string[2] { data[i].Substring(7, 3), data[i].Substring(12, 3) };
        }
        string directions = data[0];
        string current = "AAA";
        int index = 0;
        int steps = 0;
        while (current != "ZZZ")
        {
            current = network[current][directions[index] == 'L' ? 0 : 1];
            index = (index + 1) % data[0].Length;
            steps++;
        }
        return steps;
    }

    static long Part2(string[] data)
    {
        Dictionary<string, string[]> network = new Dictionary<string, string[]>();
        List<string> current = new List<string>();
        for (int i = 2; i < data.Length; i++)
        {
            network[data[i].Substring(0, 3)] = new string[2] { data[i].Substring(7, 3), data[i].Substring(12, 3) };
            if (data[i][2] == 'A')
            {
                current.Add(data[i].Substring(0, 3));
            }
        }
        string directions = data[0];
        int[] answers = new int[current.Count];
        for (int i = 0; i < current.Count; i++)
        {
            int index = 0;
            int steps = 0;
            while (current[i][2] != 'Z')
            {
                current[i] = network[current[i]][directions[index] == 'L' ? 0 : 1];
                index = (index + 1) % data[0].Length;
                steps++;
            }
            answers[i] = steps;
        }
        long lcm = answers[0];
        for (int i = 1; i < answers.Length; i++)
        {
            lcm = LCM(lcm, answers[i]);
        }
        return lcm;
    }

    static long GCD(long a, long b)
    {
        while (b != 0)
        {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    static long LCM(long a, long b)
    {
        return a / GCD(a, b) * b;
    }
}
