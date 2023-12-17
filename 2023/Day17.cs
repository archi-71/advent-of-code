class Day17
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        HashSet<string> visited = new HashSet<string>();
        PriorityQueue<List<int[]>, int> frontier = new PriorityQueue<List<int[]>, int>();
        frontier.Enqueue(new List<int[]> { new int[] { 0, 0, 0, 1, 0 } }, 0);
        frontier.Enqueue(new List<int[]> { new int[] { 0, 0, 1, 0, 0 } }, 0);
        //visited.Add("0-0-0-0");
        while (frontier.Count > 0)
        {
            frontier.TryDequeue(out List<int[]> path, out int priority);
            int[] current = path[path.Count - 1];
            if (current[0] == data.Length - 1 && current[1] == data[0].Length - 1)
            {
                return priority;
            }
            foreach (int[] dir in new int[][] { new int[] { 1, 0 }, new int[] { -1, -0 }, new int[] { 0, 1 }, new int[] { 0, -1 } })
            {
                if (dir[0] == -current[2] && dir[1] == -current[3])
                {
                    continue;
                }
                int[] next = new int[] { current[0] + dir[0], current[1] + dir[1], dir[0], dir[1],
                    dir[0] == current[2] && dir[1] == current[3] ? current[4] + 1 : 1};
                if (next[4] > 3)
                {
                    continue;
                }
                if (next[0] >= 0 && next[0] < data.Length && next[1] >= 0 && next[1] < data[0].Length && !visited.Contains(string.Join('-', next)))
                {
                    List<int[]> newPath = new List<int[]>(path) { next };
                    visited.Add(string.Join('-', next));
                    frontier.Enqueue(newPath, priority + data[next[0]][next[1]] - '0');
                }
            }
        }
        return -1;
    }

    static int Part2(string[] data)
    {
        HashSet<string> visited = new HashSet<string>();
        PriorityQueue<List<int[]>, int> frontier = new PriorityQueue<List<int[]>, int>();
        frontier.Enqueue(new List<int[]> { new int[] { 0, 0, 0, 1, 0 } }, 0);
        frontier.Enqueue(new List<int[]> { new int[] { 0, 0, 1, 0, 0 } }, 0);
        while (frontier.Count > 0)
        {
            frontier.TryDequeue(out List<int[]> path, out int priority);
            int[] current = path[path.Count - 1];
            if (current[4] >= 4 && current[0] == data.Length - 1 && current[1] == data[0].Length - 1)
            {
                return priority;
            }
            foreach (int[] dir in new int[][] { new int[] { 1, 0 }, new int[] { -1, -0 }, new int[] { 0, 1 }, new int[] { 0, -1 } })
            {
                if (dir[0] == -current[2] && dir[1] == -current[3])
                {
                    continue;
                }
                if (dir[0] == current[2] && dir[1] == current[3] && current[4] >= 10)
                {
                    continue;
                }
                if ((dir[0] != current[2] || dir[1] != current[3]) && current[4] < 4)
                {
                    continue;
                }
                int[] next = new int[] { current[0] + dir[0], current[1] + dir[1], dir[0], dir[1],
                    dir[0] == current[2] && dir[1] == current[3] ? current[4] + 1 : 1};
                if (next[0] >= 0 && next[0] < data.Length && next[1] >= 0 && next[1] < data[0].Length && !visited.Contains(string.Join('-', next)))
                {
                    List<int[]> newPath = new List<int[]>(path) { next };
                    visited.Add(string.Join('-', next));
                    frontier.Enqueue(newPath, priority + data[next[0]][next[1]] - '0');
                }
            }
        }
        return -1;
    }
}
