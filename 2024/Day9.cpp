#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

long long part1(const std::string &input)
{
    long long checksum = 0;
    int start = 0;
    int end = input.length() - 1;
    int endRemaining = input[end] - '0';
    int index = 0;
    while (start < end)
    {
        for (int i = 0; i < input[start] - '0'; i++)
        {
            checksum += index * start / 2;
            index++;
        }
        start++;
        for (int i = 0; i < input[start] - '0'; i++)
        {
            if (endRemaining == 0)
            {
                end -= 2;
                if (start >= end)
                {
                    break;
                }
                endRemaining = input[end] - '0';
            }
            endRemaining--;
            checksum += index * end / 2;
            index++;
        }
        start++;
    }
    for (int i = 0; i < endRemaining; i++)
    {
        checksum += index * end / 2;
        index++;
    }
    return checksum;
}

long long part2(const std::string &input)
{
    long long checksum = 0;
    int index = 0;
    std::unordered_set<int> used;
    for (int i = 0; i < input.length(); i += 2)
    {
        int file = input[i] - '0';
        if (used.find(i) == used.end())
        {
            used.insert(i);
            for (int j = 0; j < file; j++)
            {
                checksum += index * i / 2;
                index++;
            }
        }
        else
        {
            index += file;
        }
        int space = input[i + 1] - '0';
        bool spaceFull = false;
        while (!spaceFull)
        {
            int initialIndex = index;
            for (int j = input.length() - 1; j > i; j -= 2)
            {
                int file = input[j] - '0';
                if (file <= space && used.find(j) == used.end())
                {
                    used.insert(j);
                    for (int k = 0; k < file; k++)
                    {
                        checksum += index * j / 2;
                        index++;
                    }
                    space -= file;
                    break;
                }
            }
            if (initialIndex == index)
            {
                spaceFull = true;
            }
        }
        index += space;
    }
    return checksum;
}

int main()
{
    std::ifstream file("input.txt");
    std::string input;
    std::getline(file, input);
    file.close();

    fprintf(stdout, "Part 1 Answer: %lld\n", part1(input));
    fprintf(stdout, "Part 2 Answer: %lld\n", part2(input));

    return 0;
}