class Day16
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        return ComputeEnergizedTiles(data, new int[] { 0, 0, 0, 1 });
    }

    static int Part2(string[] data)
    {
        int max = 0;
        for (int i = 0; i < data.Length; i++)
        {
            max = Math.Max(max, ComputeEnergizedTiles(data, new int[] { i, 0, 0, 1 }));
            max = Math.Max(max, ComputeEnergizedTiles(data, new int[] { i, data[0].Length, 0, -1 }));
        }
        for (int j = 0; j < data[0].Length; j++)
        {
            max = Math.Max(max, ComputeEnergizedTiles(data, new int[] { 0, j, 1, 0 }));
            max = Math.Max(max, ComputeEnergizedTiles(data, new int[] { data.Length, j, -1, 0 }));
        }
        return max;
    }

    static int ComputeEnergizedTiles(string[] data, int[] startBeam)
    {
        HashSet<string> energized = new HashSet<string>();
        HashSet<string> visited = new HashSet<string>();
        Queue<int[]> beams = new Queue<int[]>();
        beams.Enqueue(startBeam);
        while (beams.Count() > 0)
        {
            int[] beam = beams.Dequeue();
            energized.Add(beam[0] + "," + beam[1]);
            int i = beam[2];
            int j = beam[3];
            while (beam[0] + i >= 0 && beam[0] + i < data.Length && beam[1] + j >= 0 && beam[1] + j < data[0].Length
                && (data[beam[0] + i][beam[1] + j] == '.'
                || ((data[beam[0] + i][beam[1] + j] == '-' && beam[2] == 0)
                || (data[beam[0] + i][beam[1] + j] == '|' && beam[3] == 0))))
            {
                energized.Add((beam[0] + i) + "," + (beam[1] + j));
                i += beam[2];
                j += beam[3];
            }
            if (beam[0] + i >= 0 && beam[0] + i < data.Length && beam[1] + j >= 0 && beam[1] + j >= 0 && beam[1] + j < data[0].Length)
            {
                if (data[beam[0] + i][beam[1] + j] != '\\' && !visited.Contains((beam[0] + i) + "," + (beam[1] + j) + "," + (-beam[3]) + "," + (-beam[2])))
                {
                    beams.Enqueue(new int[] { beam[0] + i, beam[1] + j, -beam[3], -beam[2] });
                    visited.Add((beam[0] + i) + "," + (beam[1] + j) + "," + (-beam[3]) + "," + (-beam[2]));
                }
                if (data[beam[0] + i][beam[1] + j] != '/' && !visited.Contains((beam[0] + i) + "," + (beam[1] + j) + "," + beam[3] + "," + beam[2]))
                {
                    beams.Enqueue(new int[] { beam[0] + i, beam[1] + j, beam[3], beam[2] });
                    visited.Add((beam[0] + i) + "," + (beam[1] + j) + "," + beam[3] + "," + beam[2]);
                }
            }
        }
        return energized.Count();
    }
}
