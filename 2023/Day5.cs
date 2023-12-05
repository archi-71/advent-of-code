class Day5
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static long Part1(string[] data)
    {
        List<long[]>[] mappings = new List<long[]>[7];
        int line = 3;
        for (int i = 0; i < 7; i++)
        {
            mappings[i] = new List<long[]>();
            while (line < data.Length && data[line].Length > 0)
            {
                mappings[i].Add(Array.ConvertAll(data[line].Split(" "), long.Parse));
                line++;
            }
            line += 2;
        }
        long[] seeds = Array.ConvertAll(data[0].Substring(7).Split(" "), long.Parse);
        long lowest = int.MaxValue;
        foreach (long seed in seeds)
        {
            long val = seed;
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < mappings[i].Count; j++)
                {
                    if (val >= mappings[i][j][1] && val < mappings[i][j][1] + mappings[i][j][2])
                    {
                        val = val + mappings[i][j][0] - mappings[i][j][1];
                        break;
                    }
                }
            }
            lowest = Math.Min(lowest, val);
        }
        return lowest;
    }

    static long Part2(string[] data)
    {
        List<long[]>[] mappings = new List<long[]>[7];
        int line = 3;
        for (int i = 0; i < 7; i++)
        {
            mappings[i] = new List<long[]>();
            while (line < data.Length && data[line].Length > 0)
            {
                mappings[i].Add(Array.ConvertAll(data[line].Split(" "), long.Parse));
                line++;
            }
            mappings[i] = mappings[i].OrderBy(x => x[1]).ToList();
            line += 2;
        }
        List<long> vals = new List<long>();
        foreach (string seed in data[0].Substring(7).Split(" "))
        {
            vals.Add(long.Parse(seed));
        }
        for (int i = 0; i < 7; i++)
        {
            List<long> newvals = new List<long>();
            for (int v = 0; v < vals.Count; v += 2)
            {
                long current = vals[v];
                for (int j = 0; j < mappings[i].Count; j++)
                {
                    if (vals[v] < mappings[i][j][1] + mappings[i][j][2] && mappings[i][j][1] < vals[v] + vals[v + 1])
                    {
                        long start = Math.Max(vals[v], mappings[i][j][1]);
                        long end = Math.Min(vals[v] + vals[v + 1], mappings[i][j][1] + mappings[i][j][2]);
                        if (start != current)
                        {
                            newvals.Add(current);
                            newvals.Add(start - current);
                        }
                        newvals.Add(start + mappings[i][j][0] - mappings[i][j][1]);
                        newvals.Add(end - start);
                        current = end;
                    }
                }
                if (current == vals[v])
                {
                    newvals.Add(vals[v]);
                    newvals.Add(vals[v + 1]);
                }
            }
            vals = newvals;
        }
        long lowest = int.MaxValue;
        for (int i = 0; i < vals.Count; i++)
        {
            if (i % 2 == 0)
            {
                lowest = Math.Min(lowest, vals[i]);
            }
        }
        return lowest;
    }
}
