class Day9
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
        foreach (string line in data)
        {
            total += findNext(Array.ConvertAll(line.Split(" "), int.Parse));
        }
        return total;
    }

    static int Part2(string[] data)
    {
        int total = 0;
        foreach (string line in data)
        {
            int[] sequence = Array.ConvertAll(line.Split(" "), int.Parse);
            Array.Reverse(sequence);
            total += findNext(sequence);
        }
        return total;
    }

    static int findNext(int[] sequence)
    {
        bool end = true;
        int[] differences = new int[sequence.Length - 1];
        for (int i = 0; i < differences.Length; i++)
        {
            differences[i] = sequence[i + 1] - sequence[i];
            if (differences[i] != 0)
            {
                end = false;
            }
        }
        if (end)
        {
            return sequence[0];
        }
        return sequence[sequence.Length - 1] + findNext(differences);
    }
}
