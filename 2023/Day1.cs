class Day1
{
    static void Main()
    {
        List<string> data = new List<string>();
        StreamReader reader = new StreamReader("input.txt");
        string? line = reader.ReadLine();
        while (line != null)
        {
            data.Add(line);
            line = reader.ReadLine();
        }
        reader.Close();

        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(List<string> data)
    {
        int total = 0;
        foreach (string line in data)
        {
            int start = 0;
            int end = line.Length - 1;
            while (!char.IsNumber(line[start]))
            {
                start++;
            }
            while (!char.IsNumber(line[end]))
            {
                end--;
            }
            total += int.Parse(line[start] + "" + line[end]);
        }
        return total;
    }

    static int Part2(List<string> data)
    {
        string[] numWords = new string[] { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
        int total = 0;
        foreach (string line in data)
        {
            int start = 0;
            int end = line.Length - 1;
            int startDigit = -1;
            int endDigit = -1;
            while (startDigit < 0)
            {
                if (char.IsNumber(line[start]))
                {
                    startDigit = int.Parse(line[start].ToString());
                }
                else
                {
                    bool foundWord = false;
                    for (int i = 0; i < numWords.Length; i++)
                    {
                        if (start + numWords[i].Length <= line.Length
                                && line.Substring(start, numWords[i].Length) == numWords[i])
                        {
                            startDigit = i + 1;
                            foundWord = true;
                            break;
                        }
                    }
                    if (!foundWord)
                    {
                        start++;
                    }
                }
            }
            while (endDigit < 0)
            {
                if (char.IsNumber(line[end]))
                {
                    endDigit = int.Parse(line[end].ToString());
                }
                else
                {
                    bool foundWord = false;
                    for (int i = 0; i < numWords.Length; i++)
                    {
                        if (end - numWords[i].Length >= 0
                                && line.Substring(end - numWords[i].Length + 1, numWords[i].Length) == numWords[i])
                        {
                            endDigit = i + 1;
                            foundWord = true;
                            break;
                        }
                    }
                    if (!foundWord)
                    {
                        end--;
                    }
                }
            }
            total += startDigit * 10 + endDigit;
        }
        return total;
    }
}
