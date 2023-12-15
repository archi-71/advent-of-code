class Day15
{
    static void Main()
    {
        string[] data = File.ReadAllText("input.txt").Split(',');
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        int total = 0;
        foreach (string step in data)
        {
            int hash = 0;
            foreach (char c in step)
            {
                hash += (int)c;
                hash *= 17;
                hash %= 256;
            }
            total += hash;
        }
        return total;
    }

    static int Part2(string[] data)
    {
        List<KeyValuePair<string, int>>[] boxes = new List<KeyValuePair<string, int>>[256];
        foreach (string step in data)
        {
            int index = 0;
            while (char.IsLetter(step[index]))
            {
                index++;
            }
            string label = step.Substring(0, index);
            int hash = 0;
            foreach (char c in label)
            {
                hash += (int)c;
                hash *= 17;
                hash %= 256;
            }
            List<KeyValuePair<string, int>> list = boxes[hash];
            if (step[index] == '-')
            {
                if (list != null)
                {
                    for (int i = 0; i < list.Count; i++)
                    {
                        if (list[i].Key == label)
                        {
                            list.RemoveAt(i);
                            break;
                        }
                    }
                }
            }
            else
            {
                if (list == null)
                {
                    boxes[hash] = new List<KeyValuePair<string, int>> { new KeyValuePair<string, int>(label, step[index + 1] - '0') };
                }
                else
                {
                    bool found = false;
                    for (int i = 0; i < list.Count; i++)
                    {
                        if (list[i].Key == label)
                        {
                            list[i] = new KeyValuePair<string, int>(label, step[index + 1] - '0');
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        list.Add(new KeyValuePair<string, int>(label, step[index + 1] - '0'));
                    }
                }
            }
        }
        int total = 0;
        for (int i = 0; i < boxes.Length; i++)
        {
            if (boxes[i] != null)
            {
                for (int j = 0; j < boxes[i].Count; j++)
                {
                    total += (i + 1) * (j + 1) * boxes[i][j].Value;
                }
            }
        }
        return total;
    }
}
