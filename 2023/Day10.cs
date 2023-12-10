using System.Numerics;

class Day10
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        int[] start = new int[2];
        for (int i = 0; i < data.Length; i++)
        {
            for (int j = 0; j < data[0].Length; j++)
            {
                if (data[i][j] == 'S')
                {
                    start = new int[] { i, j };
                    break;
                }
            }
        }
        Dictionary<char, int[][]> pipes = new Dictionary<char, int[][]> {
            { '|', new int[][] { new int[] { -1, 0 }, new int[] { 1, 0 } } },
            { '-', new int[][] { new int[] { 0, -1 }, new int[] { 0, 1 } } },
            { 'L', new int[][] { new int[] { -1, 0 }, new int[] { 0, 1 } } },
            { 'J', new int[][] { new int[] { -1, 0 }, new int[] { 0, -1 } } },
            { '7', new int[][] { new int[] { 1, 0 }, new int[] { 0, -1 } } },
            { 'F', new int[][] { new int[] { 1, 0 }, new int[] { 0, 1 } } },
            { '.', new int[0][] }
        };
        int[] current = new int[2];
        for (int i = -1; i < 2; i += 2)
        {
            if (start[0] + i >= 0 && start[0] + i < data.Length)
            {
                foreach (int[] dir in pipes[data[start[0] + i][start[1]]])
                {
                    if (dir[0] == -i && dir[1] == 0)
                    {
                        current = new int[] { start[0] + i, start[1] };
                    }
                }
            }
        }
        for (int j = -1; j < 2; j += 2)
        {
            if (start[1] + j >= 0 && start[1] + j < data[0].Length)
            {
                foreach (int[] dir in pipes[data[start[0]][start[1] + j]])
                {
                    if (dir[0] == 0 && dir[1] == -j)
                    {
                        current = new int[] { start[0], start[1] + j };
                    }
                }
            }
        }
        int[] prev = start;
        int length = 1;
        do
        {
            foreach (int[] dir in pipes[data[current[0]][current[1]]])
            {
                if (current[0] + dir[0] >= 0 && current[0] + dir[0] < data.Length && current[1] + dir[1] >= 0 && current[1] + dir[1] < data[0].Length)
                {
                    if (!(current[0] + dir[0] == prev[0] && current[1] + dir[1] == prev[1]))
                    {
                        prev = current;
                        current = new int[] { current[0] + dir[0], current[1] + dir[1] };
                        break;
                    }
                }
            }
            length++;
        } while (current[0] != start[0] || current[1] != start[1]);
        return length / 2;
    }

    static int Part2(string[] data)
    {
        Dictionary<char, int[][]> pipes = new Dictionary<char, int[][]> {
            { '|', new int[][] { new int[] { -1, 0 }, new int[] { 1, 0 } } },
            { '-', new int[][] { new int[] { 0, -1 }, new int[] { 0, 1 } } },
            { 'L', new int[][] { new int[] { -1, 0 }, new int[] { 0, 1 } } },
            { 'J', new int[][] { new int[] { -1, 0 }, new int[] { 0, -1 } } },
            { '7', new int[][] { new int[] { 1, 0 }, new int[] { 0, -1 } } },
            { 'F', new int[][] { new int[] { 1, 0 }, new int[] { 0, 1 } } },
            { '.', new int[0][] }
        };
        int[] start = new int[2];
        for (int i = 0; i < data.Length; i++)
        {
            for (int j = 0; j < data[0].Length; j++)
            {
                if (data[i][j] == 'S')
                {
                    start = new int[] { i, j };
                    break;
                }
            }
        }
        foreach (char pipe in pipes.Keys)
        {
            bool possiblePipe = true;
            foreach (int[] dir in pipes[pipe])
            {
                if (start[0] + dir[0] >= 0 && start[0] + dir[0] < data.Length && start[1] + dir[1] >= 0 && start[1] + dir[1] < data[0].Length)
                {
                    bool connecting = false;
                    foreach (int[] dir2 in pipes[data[start[0] + dir[0]][start[1] + dir[1]]])
                    {
                        if (start[0] == start[0] + dir[0] + dir2[0] && start[1] == start[1] + dir[1] + dir2[1])
                        {
                            connecting = true;
                            break;
                        }
                    }
                    if (!connecting)
                    {
                        possiblePipe = false;
                        break;
                    }
                }
                else
                {
                    possiblePipe = false;
                    break;
                }
            }
            if (possiblePipe)
            {
                data[start[0]] = data[start[0]].Substring(0, start[1]) + pipe + data[start[0]].Substring(start[1] + 1);
                break;
            }
        }
        bool[,] path = new bool[data.Length, data[0].Length];
        path[start[0], start[1]] = true;
        int[] prev = new int[2];
        int[] current = start;
        do
        {
            foreach (int[] dir in pipes[data[current[0]][current[1]]])
            {
                if (current[0] + dir[0] >= 0 && current[0] + dir[0] < data.Length && current[1] + dir[1] >= 0 && current[1] + dir[1] < data[0].Length)
                {
                    if (!(current[0] + dir[0] == prev[0] && current[1] + dir[1] == prev[1]))
                    {
                        path[current[0], current[1]] = true;
                        prev = current;
                        current = new int[] { current[0] + dir[0], current[1] + dir[1] };
                        break;
                    }
                }
            }
        } while (current[0] != start[0] || current[1] != start[1]);
        int count = 0;
        for (int i = 0; i < data.Length; i++)
        {
            bool inside = false;
            char lastPipe = '\0';
            for (int j = 0; j < data[0].Length; j++)
            {
                if (path[i, j])
                {
                    if (data[i][j] != '-' && !(data[i][j] == 'J' && lastPipe == 'F') && !(data[i][j] == '7' && lastPipe == 'L'))
                    {
                        inside = !inside;
                        lastPipe = data[i][j];
                    }
                }
                else if (inside)
                {
                    count++;
                }
            }
        }
        return count;
    }
}
