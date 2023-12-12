using System.Text.RegularExpressions;

class Day12
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
            string[] lineArray = line.Split(" ");
            char[] damaged = Regex.Replace(lineArray[0].Trim(new char[] { '.' }), @"\.+", ".").ToCharArray();
            int[] groups = Array.ConvertAll(lineArray[1].Split(","), int.Parse);
            int[,] M = new int[damaged.Length, groups.Length];
            for (int i = 0; i < damaged.Length; i++)
            {
                for (int j = 0; j < groups.Length; j++)
                {
                    if (i + 1 < groups.Take(j + 1).Sum() + j)
                    {
                        M[i, j] = 0;
                        continue;
                    }
                    if (i == 0)
                    {
                        M[i, j] = j > 0 || groups[j] > 1 ? 0 : 1;
                    }
                    else
                    {
                        M[i, j] = 0;
                        if (damaged[i] != '#')
                        {
                            M[i, j] += M[i - 1, j];
                        }
                        if (damaged[i] != '.')
                        {
                            bool valid = true;
                            for (int k = i - groups[j] + 1; k < i; k++)
                            {
                                if (k < 0 || damaged[k] == '.')
                                {
                                    valid = false;
                                }
                            }
                            if (valid)
                            {
                                if (i - groups[j] < 0)
                                {
                                    M[i, j] += j > 0 ? 0 : 1;
                                }
                                else if (damaged[i - groups[j]] != '#')
                                {
                                    if (j == 0)
                                    {
                                        for (int k = i - groups[j]; k > -1; k--)
                                        {
                                            if (damaged[k] == '#')
                                            {
                                                valid = false;
                                            }
                                        }
                                        M[i, j] += valid ? 1 : 0;
                                    }
                                    else
                                    {
                                        if (i - groups[j] - 1 < 0)
                                        {
                                            M[i, j] += damaged[i - groups[j]] == '?' ? 0 : 1;
                                        }
                                        else
                                        {
                                            M[i, j] += M[i - groups[j] - 1, j - 1];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            total += M[damaged.Length - 1, groups.Length - 1];
        }
        return total;
    }

    static long Part2(string[] data)
    {
        long total = 0;
        foreach (string line in data)
        {
            string[] lineArray = line.Split(" ");
            char[] damaged = Regex.Replace("X?X?X?X?X".Replace("X", lineArray[0]).Trim(new char[] { '.' }), @"\.+", ".").ToCharArray();
            int[] groups = Array.ConvertAll("X,X,X,X,X".Replace("X", lineArray[1]).Split(","), int.Parse);
            long[,] M = new long[damaged.Length, groups.Length];
            for (int i = 0; i < damaged.Length; i++)
            {
                for (int j = 0; j < groups.Length; j++)
                {
                    if (i + 1 < groups.Take(j + 1).Sum() + j)
                    {
                        M[i, j] = 0;
                        continue;
                    }
                    if (i == 0)
                    {
                        M[i, j] = j > 0 || groups[j] > 1 ? 0 : 1;
                    }
                    else
                    {
                        M[i, j] = 0;
                        if (damaged[i] != '#')
                        {
                            M[i, j] += M[i - 1, j];
                        }
                        if (damaged[i] != '.')
                        {
                            bool valid = true;
                            for (int k = i - groups[j] + 1; k < i; k++)
                            {
                                if (k < 0 || damaged[k] == '.')
                                {
                                    valid = false;
                                }
                            }
                            if (valid)
                            {
                                if (i - groups[j] < 0)
                                {
                                    M[i, j] += 1;
                                }
                                else if (damaged[i - groups[j]] != '#')
                                {
                                    if (j == 0)
                                    {
                                        for (int k = i - groups[j]; k > -1; k--)
                                        {
                                            if (damaged[k] == '#')
                                            {
                                                valid = false;
                                            }
                                        }
                                        M[i, j] += valid ? 1 : 0;
                                    }
                                    else
                                    {
                                        if (i - groups[j] - 1 < 0)
                                        {
                                            M[i, j] += damaged[i - groups[j]] == '?' ? 0 : 1;
                                        }
                                        else
                                        {
                                            M[i, j] += M[i - groups[j] - 1, j - 1];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            total += M[damaged.Length - 1, groups.Length - 1];
        }
        return total;
    }
}
