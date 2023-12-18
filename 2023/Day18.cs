class Day18
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static long Part1(string[] data)
    {
        Dictionary<string, int[]> directions = new Dictionary<string, int[]>() { { "D", new int[2] { 1, 0 } }, { "U", new int[2] { -1, 0 } }, { "R", new int[2] { 0, 1 } }, { "L", new int[2] { 0, -1 } } };
        List<long[]> points = new List<long[]>() { new long[] { 0, 0 } };
        for (int i = 0; i < data.Length - 1; i++)
        {
            string[] lineArray = data[i].Split(" ");
            int[] dir = directions[lineArray[0]];
            int length = int.Parse(lineArray[1]);
            points.Add(new long[] { points[points.Count - 1][0] + dir[0] * length, points[points.Count - 1][1] + dir[1] * length });
        }
        List<long[]> exteriorPoints = new List<long[]>();
        for (int i = 0; i < points.Count; i++)
        {
            long[] prev = points[(i - 1 + points.Count) % points.Count];
            long[] next = points[(i + 1) % points.Count];
            long[] dir = new long[] { Math.Sign(prev[0] - points[i][0] + next[0] - points[i][0]), Math.Sign(prev[1] - points[i][1] + next[1] - points[i][1]) };
            long[] distantPoint = new long[] { points[i][0] + dir[0] * int.MaxValue, points[i][1] + dir[1] * int.MaxValue };
            int intersections = 0;
            for (int j = 0; j < points.Count; j++)
            {
                if (i != j && i != (j + 1) % points.Count && Intersecting(points[i], distantPoint, points[j], points[(j + 1) % points.Count]))
                {
                    intersections++;
                }
            }
            if (intersections % 2 == 0)
            {
                exteriorPoints.Add(new long[] { points[i][0] + (dir[0] > 0 ? 1 : 0), points[i][1] + (dir[1] < 0 ? -1 : 0) });
            }
            else
            {
                exteriorPoints.Add(new long[] { points[i][0] + (dir[0] < 0 ? 1 : 0), points[i][1] + (dir[1] > 0 ? -1 : 0) });
            }
        }
        long area = 0;
        for (int i = 0; i < exteriorPoints.Count; i++)
        {
            area += exteriorPoints[i][0] * exteriorPoints[(i + 1) % exteriorPoints.Count][1] - exteriorPoints[i][1] * exteriorPoints[(i + 1) % exteriorPoints.Count][0];
        }
        return Math.Abs(area / 2);
    }

    static long Part2(string[] data)
    {
        Dictionary<char, int[]> directions = new Dictionary<char, int[]>() { { '0', new int[2] { 1, 0 } }, { '1', new int[2] { 0, -1 } }, { '2', new int[2] { -1, 0 } }, { '3', new int[2] { 0, 1 } } };
        List<long[]> points = new List<long[]>() { new long[] { 0, 0 } };
        for (int i = 0; i < data.Length - 1; i++)
        {
            string hex = data[i].Split(" ")[2].Substring(2, 6);
            int[] dir = directions[hex[5]];
            int length = Convert.ToInt32(hex.Substring(0, 5), 16);
            points.Add(new long[] { points[points.Count - 1][0] + dir[0] * length, points[points.Count - 1][1] + dir[1] * length });
        }
        List<long[]> exteriorPoints = new List<long[]>();
        for (int i = 0; i < points.Count; i++)
        {
            long[] prev = points[(i - 1 + points.Count) % points.Count];
            long[] next = points[(i + 1) % points.Count];
            long[] dir = new long[] { Math.Sign(prev[0] - points[i][0] + next[0] - points[i][0]), Math.Sign(prev[1] - points[i][1] + next[1] - points[i][1]) };
            long[] distantPoint = new long[] { points[i][0] + dir[0] * int.MaxValue, points[i][1] + dir[1] * int.MaxValue };
            int intersections = 0;
            for (int j = 0; j < points.Count; j++)
            {
                if (i != j && i != (j + 1) % points.Count && Intersecting(points[i], distantPoint, points[j], points[(j + 1) % points.Count]))
                {
                    intersections++;
                }
            }
            if (intersections % 2 == 0)
            {
                exteriorPoints.Add(new long[] { points[i][0] + (dir[0] > 0 ? 1 : 0), points[i][1] + (dir[1] < 0 ? -1 : 0) });
            }
            else
            {
                exteriorPoints.Add(new long[] { points[i][0] + (dir[0] < 0 ? 1 : 0), points[i][1] + (dir[1] > 0 ? -1 : 0) });
            }
        }
        long area = 0;
        for (int i = 0; i < exteriorPoints.Count; i++)
        {
            area += exteriorPoints[i][0] * exteriorPoints[(i + 1) % exteriorPoints.Count][1] - exteriorPoints[i][1] * exteriorPoints[(i + 1) % exteriorPoints.Count][0];
        }
        return Math.Abs(area / 2);
    }

    static bool CCW(long[] A, long[] B, long[] C)
    {
        return (C[1] - A[1]) * (B[0] - A[0]) > (B[1] - A[1]) * (C[0] - A[0]);
    }

    static bool Intersecting(long[] A, long[] B, long[] C, long[] D)
    {
        return CCW(A, C, D) != CCW(B, C, D) && CCW(A, B, C) != CCW(A, B, D);
    }
}
