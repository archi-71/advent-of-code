class Day14
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        char[,] grid = new char[data.Length, data[0].Length];
        for (int i = 0; i < data.Length; i++)
        {
            for (int j = 0; j < data.Length; j++)
            {
                grid[i, j] = data[i][j];
            }
        }
        Console.WriteLine("Part 1 Answer: " + Part1(grid));
        Console.WriteLine("Part 2 Answer: " + Part2(grid));
    }

    static int Part1(char[,] grid)
    {
        int total = 0;
        for (int i = 0; i < grid.GetLength(1); i++)
        {
            int lastStop = -1;
            for (int j = 0; j < grid.GetLength(0); j++)
            {
                if (grid[j, i] == '#')
                {
                    lastStop = j;
                }
                else if (grid[j, i] == 'O')
                {
                    total += grid.GetLength(0) - (lastStop + 1);
                    lastStop++;
                }
            }
        }
        return total;
    }

    static int Part2(char[,] grid)
    {
        List<char[,]> history = new List<char[,]>();
        char[,] copy = new char[grid.GetLength(0), grid.GetLength(1)];
        Array.Copy(grid, copy, grid.Length);
        history.Add(copy);
        for (int n = 0; n < 1000000000; n++)
        {
            for (int i = 0; i < grid.GetLength(1); i++)
            {
                int lastStop = -1;
                for (int j = 0; j < grid.GetLength(0); j++)
                {
                    if (grid[j, i] == '#')
                    {
                        lastStop = j;
                    }
                    else if (grid[j, i] == 'O')
                    {
                        grid[j, i] = '.';
                        grid[lastStop + 1, i] = 'O';
                        lastStop++;
                    }
                }
            }
            for (int i = 0; i < grid.GetLength(0); i++)
            {
                int lastStop = -1;
                for (int j = 0; j < grid.GetLength(1); j++)
                {
                    if (grid[i, j] == '#')
                    {
                        lastStop = j;
                    }
                    else if (grid[i, j] == 'O')
                    {
                        grid[i, j] = '.';
                        grid[i, lastStop + 1] = 'O';
                        lastStop++;
                    }
                }
            }
            for (int i = 0; i < grid.GetLength(1); i++)
            {
                int lastStop = grid.GetLength(0);
                for (int j = grid.GetLength(0) - 1; j >= 0; j--)
                {
                    if (grid[j, i] == '#')
                    {
                        lastStop = j;
                    }
                    else if (grid[j, i] == 'O')
                    {
                        grid[j, i] = '.';
                        grid[lastStop - 1, i] = 'O';
                        lastStop--;
                    }
                }
            }
            for (int i = 0; i < grid.GetLength(0); i++)
            {
                int lastStop = grid.GetLength(1);
                for (int j = grid.GetLength(1) - 1; j >= 0; j--)
                {
                    if (grid[i, j] == '#')
                    {
                        lastStop = j;
                    }
                    else if (grid[i, j] == 'O')
                    {
                        grid[i, j] = '.';
                        grid[i, lastStop - 1] = 'O';
                        lastStop--;
                    }
                }
            }
            for (int k = 0; k < history.Count; k++)
            {
                bool match = true;
                for (int i = 0; i < grid.GetLength(0); i++)
                {
                    for (int j = 0; j < grid.GetLength(1); j++)
                    {
                        if (grid[i, j] != history[k][i, j])
                        {
                            match = false;
                            break;
                        }
                    }
                }
                if (match)
                {
                    int index = k + (1000000000 - k) % (n + 1 - k);
                    int total = 0;
                    for (int i = 0; i < grid.GetLength(0); i++)
                    {
                        for (int j = 0; j < grid.GetLength(1); j++)
                        {
                            if (history[index][i, j] == 'O')
                            {
                                total += grid.GetLength(0) - i;
                            }
                        }
                    }
                    return total;
                }
            }
            copy = new char[grid.GetLength(0), grid.GetLength(1)];
            Array.Copy(grid, copy, grid.Length);
            history.Add(copy);
        }
        return -1;
    }
}
