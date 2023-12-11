class Day11
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        int[] rowGaps = new int[data.Length];
        int gaps = 0;
        for (int i = 0; i < data.Length; i++)
        {
            rowGaps[i] = gaps;
            bool rowEmpty = true;
            for (int j = 0; j < data[0].Length; j++)
            {
                if (data[i][j] == '#')
                {
                    rowEmpty = false;
                }
            }
            if (rowEmpty)
            {
                gaps++;
            }
        }
        int[] colGaps = new int[data[0].Length];
        gaps = 0;
        for (int i = 0; i < data[0].Length; i++)
        {
            colGaps[i] = gaps;
            bool colEmpty = true;
            for (int j = 0; j < data.Length; j++)
            {
                if (data[j][i] == '#')
                {
                    colEmpty = false;
                }
            }
            if (colEmpty)
            {
                gaps++;
            }
        }
        List<int[]> pairs = new List<int[]>();
        for (int i = 0; i < data.Length; i++)
        {
            for (int j = 0; j < data[0].Length; j++)
            {
                if (data[i][j] == '#')
                {
                    pairs.Add(new int[] { i + rowGaps[i], j + colGaps[j] });
                }
            }
        }
        int total = 0;
        for (int i = 0; i < pairs.Count - 1; i++)
        {
            for (int j = i + 1; j < pairs.Count; j++)
            {
                total += Math.Abs(pairs[i][0] - pairs[j][0]) + Math.Abs(pairs[i][1] - pairs[j][1]);
            }
        }
        return total;
    }

    static long Part2(string[] data)
    {
        int[] rowGaps = new int[data.Length];
        int gaps = 0;
        for (int i = 0; i < data.Length; i++)
        {
            rowGaps[i] = gaps;
            bool rowEmpty = true;
            for (int j = 0; j < data[0].Length; j++)
            {
                if (data[i][j] == '#')
                {
                    rowEmpty = false;
                }
            }
            if (rowEmpty)
            {
                gaps++;
            }
        }
        int[] colGaps = new int[data[0].Length];
        gaps = 0;
        for (int i = 0; i < data[0].Length; i++)
        {
            colGaps[i] = gaps;
            bool colEmpty = true;
            for (int j = 0; j < data.Length; j++)
            {
                if (data[j][i] == '#')
                {
                    colEmpty = false;
                }
            }
            if (colEmpty)
            {
                gaps++;
            }
        }
        List<long[]> pairs = new List<long[]>();
        for (int i = 0; i < data.Length; i++)
        {
            for (int j = 0; j < data[0].Length; j++)
            {
                if (data[i][j] == '#')
                {
                    pairs.Add(new long[] { i + rowGaps[i] * 999999, j + colGaps[j] * 999999 });
                }
            }
        }
        long total = 0;
        for (int i = 0; i < pairs.Count - 1; i++)
        {
            for (int j = i + 1; j < pairs.Count; j++)
            {
                total += Math.Abs(pairs[i][0] - pairs[j][0]) + Math.Abs(pairs[i][1] - pairs[j][1]);
            }
        }
        return total;
    }
}
