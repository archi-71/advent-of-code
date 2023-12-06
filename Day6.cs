using System.Text.RegularExpressions;

class Day6
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        int product = 1;
        int[] times = Array.ConvertAll(Regex.Replace(data[0], @"\s+", " ").Substring(6).Split(" "), int.Parse);
        int[] distances = Array.ConvertAll(Regex.Replace(data[1], @"\s+", " ").Substring(10).Split(" "), int.Parse);
        for (int i = 0; i < times.Length; i++)
        {
            double dicriminant = Math.Sqrt(Math.Pow(times[i], 2) - 4 * distances[i]);
            int lower = (int)Math.Floor((float)((times[i] - dicriminant) / 2));
            int upper = (int)Math.Ceiling((float)((times[i] + dicriminant) / 2));
            product *= upper - lower - 1;
        }
        return product;
    }

    static long Part2(string[] data)
    {
        long time = long.Parse(Regex.Replace(data[0], @"\s+", "").Substring(5));
        long distance = long.Parse(Regex.Replace(data[1], @"\s+", "").Substring(9));
        double dicriminant = Math.Sqrt(Math.Pow(time, 2) - 4 * distance);
        long lower = (long)Math.Floor((float)((time - dicriminant) / 2));
        long upper = (long)Math.Ceiling((float)((time + dicriminant) / 2));
        return upper - lower - 1;
    }
}
