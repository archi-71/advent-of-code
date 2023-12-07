class Day7
{
    static void Main()
    {
        string[] data = File.ReadLines("input.txt").ToArray();
        Console.WriteLine("Part 1 Answer: " + Part1(data));
        Console.WriteLine("Part 2 Answer: " + Part2(data));
    }

    static int Part1(string[] data)
    {
        Dictionary<char, int> strengths = new Dictionary<char, int>() {
            {'A', 13}, {'K', 12}, {'Q', 11}, {'J', 10}, {'T', 9}, {'9', 8}, {'8', 7}, {'7', 6}, {'6', 5}, {'5', 4}, {'4', 3}, {'3', 2}, {'2', 1}
        };
        List<string[]>[] ordering = new List<string[]>[7];
        for (int i = 0; i < 7; i++)
        {
            ordering[i] = new List<string[]>();
        }
        for (int i = 0; i < data.Length; i++)
        {
            string[] handAndBid = data[i].Split(" ");
            int differences = 0;
            for (int j = 0; j < handAndBid[0].Length - 1; j++)
            {
                for (int k = j + 1; k < handAndBid[0].Length; k++)
                {
                    if (handAndBid[0][j] != handAndBid[0][k])
                    {
                        differences++;
                    }
                }
            }
            switch (differences)
            {
                case 10:
                    // High card
                    ordering[0].Add(handAndBid);
                    break;
                case 9:
                    // One pair
                    ordering[1].Add(handAndBid);
                    break;
                case 8:
                    // Two pair
                    ordering[2].Add(handAndBid);
                    break;
                case 7:
                    // Three of a kind
                    ordering[3].Add(handAndBid);
                    break;
                case 6:
                    // Full house
                    ordering[4].Add(handAndBid);
                    break;
                case 4:
                    // Four of a kind
                    ordering[5].Add(handAndBid);
                    break;
                case 0:
                    // Five of a kind
                    ordering[6].Add(handAndBid);
                    break;
            }
        }
        for (int i = 0; i < 7; i++)
        {
            ordering[i].Sort((a, b) => CompareHands(a[0], b[0], strengths));
        }
        int total = 0;
        int rank = 1;
        for (int i = 0; i < 7; i++)
        {
            foreach (string[] handAndBid in ordering[i])
            {
                total += rank * int.Parse(handAndBid[1]);
                rank++;
            }
        }
        return total;
    }

    static int Part2(string[] data)
    {
        Dictionary<char, int> strengths = new Dictionary<char, int>() {
            {'A', 13}, {'K', 12}, {'Q', 11}, {'T', 9}, {'9', 8}, {'8', 7}, {'7', 6}, {'6', 5}, {'5', 4}, {'4', 3}, {'3', 2}, {'2', 1}, {'J', 0}
        };
        List<string[]>[] ordering = new List<string[]>[7];
        for (int i = 0; i < 7; i++)
        {
            ordering[i] = new List<string[]>();
        }
        for (int i = 0; i < data.Length; i++)
        {
            string[] handAndBid = data[i].Split(" ");
            string hand = handAndBid[0];
            if (hand == "JJJJJ")
            {
                hand = "AAAAA";
            }
            else
            {
                char mostFrequent = hand.Where(x => x != 'J').GroupBy(x => x).OrderByDescending(x => x.Count()).First().Key;
                hand = hand.Replace('J', mostFrequent);
            }
            int differences = 0;
            for (int j = 0; j < 4; j++)
            {
                for (int k = j + 1; k < 5; k++)
                {
                    if (hand[j] != hand[k])
                    {
                        differences++;
                    }
                }
            }
            switch (differences)
            {
                case 10:
                    // High card
                    ordering[0].Add(handAndBid);
                    break;
                case 9:
                    // One pair
                    ordering[1].Add(handAndBid);
                    break;
                case 8:
                    // Two pair
                    ordering[2].Add(handAndBid);
                    break;
                case 7:
                    // Three of a kind
                    ordering[3].Add(handAndBid);
                    break;
                case 6:
                    // Full house
                    ordering[4].Add(handAndBid);
                    break;
                case 4:
                    // Four of a kind
                    ordering[5].Add(handAndBid);
                    break;
                case 0:
                    // Five of a kind
                    ordering[6].Add(handAndBid);
                    break;
            }
        }
        for (int i = 0; i < 7; i++)
        {
            ordering[i].Sort((a, b) => CompareHands(a[0], b[0], strengths));
        }
        int total = 0;
        int rank = 1;
        for (int i = 0; i < 7; i++)
        {
            foreach (string[] handAndBid in ordering[i])
            {
                total += rank * int.Parse(handAndBid[1]);
                rank++;
            }
        }
        return total;
    }

    static int CompareHands(string h1, string h2, Dictionary<char, int> strengths)
    {
        for (int i = 0; i < 5; i++)
        {
            if (strengths[h1[i]] > strengths[h2[i]])
            {
                return 1;
            }
            else if (strengths[h1[i]] < strengths[h2[i]])
            {
                return -1;
            }
        }
        return 0;
    }
}
