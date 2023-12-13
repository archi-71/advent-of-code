class Day13
{
    static void Main()
    {
        string[] data = File.ReadAllText("input.txt").Split("\n\n");
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        int total = 0;
        foreach (string pattern in data)
        {
            string[] rows = pattern.Split("\n");
            for (int l = 0; l < rows.Length - 1; l++)
            {
                bool reflection = true;
                for (int i = 0; i < Math.Min(l + 1, rows.Length - l - 1); i++)
                {
                    if (rows[l - i] != rows[l + i + 1])
                    {
                        reflection = false;
                        break;
                    }
                }
                if (reflection)
                {
                    total += 100 * (l + 1);
                    break;
                }
            }
            for (int l = 0; l < rows[0].Length - 1; l++)
            {
                bool reflection = true;
                for (int i = 0; i < Math.Min(l + 1, rows[0].Length - l - 1); i++)
                {
                    for (int j = 0; j < rows.Length; j++)
                    {
                        if (rows[j][l - i] != rows[j][l + i + 1])
                        {
                            reflection = false;
                            break;
                        }
                    }
                }
                if (reflection)
                {
                    total += l + 1;
                    break;
                }
            }
        }
        return total;
    }

    static int Part2(string[] data)
    {
        int total = 0;
        foreach (string pattern in data)
        {
            string[] rows = pattern.Split("\n");
            for (int l = 0; l < rows.Length - 1; l++)
            {
                int differences = 0;
                for (int i = 0; i < Math.Min(l + 1, rows.Length - l - 1); i++)
                {
                    for (int j = 0; j < rows[0].Length; j++)
                    {
                        if (rows[l - i][j] != rows[l + i + 1][j])
                        {
                            differences++;
                            if (differences > 1)
                            {
                                break;
                            }
                        }
                    }
                }
                if (differences == 1)
                {
                    total += 100 * (l + 1);
                    break;
                }
            }
            for (int l = 0; l < rows[0].Length - 1; l++)
            {
                int differences = 0;
                for (int i = 0; i < Math.Min(l + 1, rows[0].Length - l - 1); i++)
                {
                    for (int j = 0; j < rows.Length; j++)
                    {
                        if (rows[j][l - i] != rows[j][l + i + 1])
                        {
                            differences++;
                            if (differences > 1)
                            {
                                break;
                            }
                        }
                    }
                }
                if (differences == 1)
                {
                    total += l + 1;
                    break;
                }
            }
        }
        return total;
    }
}
