using System.Text.RegularExpressions;

class Day4
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
        for (int i = 0; i < data.Length; i++)
        {
            string[] line = data[i].Substring(7 + (i + 1).ToString().Length).Split(" | ");
            string[] winningCards = Regex.Replace(line[0].Trim(' '), @"\s+", " ").Split(" ");
            string[] haveCards = Regex.Replace(line[1].Trim(' '), @"\s+", " ").Split(" ");
            IEnumerable<string> haveWinners = winningCards.Intersect(haveCards);
            total += (int)Math.Pow(2, haveWinners.Count<string>() - 1);
        }
        return total;
    }

    static int Part2(string[] data)
    {
        int total = 0;
        int[] cardCopies = new int[data.Length];
        for (int i = 0; i < cardCopies.Length; i++)
        {
            cardCopies[i] = 1;
        }
        for (int i = 0; i < data.Length; i++)
        {
            string[] line = data[i].Substring(7 + (i + 1).ToString().Length).Split(" | ");
            string[] winningCards = Regex.Replace(line[0].Trim(' '), @"\s+", " ").Split(" ");
            string[] haveCards = Regex.Replace(line[1].Trim(' '), @"\s+", " ").Split(" ");
            IEnumerable<string> haveWinners = winningCards.Intersect(haveCards);
            for (int j = i + 1; j < i + 1 + haveWinners.Count<string>(); j++)
            {
                cardCopies[j] += cardCopies[i];
            }
            total += cardCopies[i];
        }
        return total;
    }
}
