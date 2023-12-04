class Day3
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
        int currentNum = 0;
        bool isPartNumber = false;
        for (int i = 0; i < data.Length; i++)
        {
            for (int j = 0; j < data[i].Length; j++)
            {
                if (char.IsNumber(data[i][j]))
                {
                    currentNum = currentNum * 10 + int.Parse(data[i][j].ToString());
                    if (!isPartNumber)
                    {
                        for (int k = -1; k < 2; k++)
                        {
                            for (int l = -1; l < 2; l++)
                            {
                                if (i + k >= 0 && j + l >= 0 && i + k < data.Length && j + l < data[i].Length)
                                {
                                    if (!(char.IsNumber(data[i + k][j + l]) || data[i + k][j + l] == '.'))
                                    {
                                        isPartNumber = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (isPartNumber)
                    {
                        total += currentNum;
                    }
                    currentNum = 0;
                    isPartNumber = false;
                }
            }
        }
        if (isPartNumber)
        {
            total += currentNum;
        }
        return total;
    }

    static int Part2(string[] data)
    {
        Dictionary<string, List<int>> gears = new Dictionary<string, List<int>>();
        int currentNum = 0;
        string? gear = null;
        for (int i = 0; i < data.Length; i++)
        {
            for (int j = 0; j < data[i].Length; j++)
            {
                if (char.IsNumber(data[i][j]))
                {
                    currentNum = currentNum * 10 + int.Parse(data[i][j].ToString());
                    if (gear == null)
                    {
                        for (int k = -1; k < 2; k++)
                        {
                            for (int l = -1; l < 2; l++)
                            {
                                if (i + k >= 0 && j + l >= 0 && i + k < data.Length && j + l < data[i].Length)
                                {
                                    if (data[i + k][j + l] == '*')
                                    {
                                        gear = (i + k) + "-" + (j + l);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (gear != null)
                    {
                        List<int>? parts;
                        if (gears.TryGetValue(gear, out parts))
                        {
                            parts.Add(currentNum);
                        }
                        else
                        {
                            gears[gear] = new List<int> { currentNum };
                        }

                    }
                    currentNum = 0;
                    gear = null;
                }
            }
        }
        int total = 0;
        List<string> gearList = new List<string>(gears.Keys);
        foreach (string g in gearList)
        {
            if (gears[g].Count() == 2)
            {
                total += gears[g][0] * gears[g][1];
            }
        }
        return total;
    }
}
