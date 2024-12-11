#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

long long solve(const std::string &input, int blinks)
{
    std::unordered_map<std::string, long long> counts;
    std::vector<std::string> stones = split(input, " ");
    for (std::string stone : stones)
    {
        counts[stone]++;
    }
    for (int i = 0; i < blinks; i++)
    {
        std::unordered_map<std::string, long long> newCounts;
        for (auto &pair : counts)
        {
            long long v = std::stoll(pair.first);
            std::string s = std::to_string(v);
            if (v == 0)
            {
                newCounts["1"] += pair.second;
            }
            else if (s.length() % 2 == 0)
            {
                int half = s.length() / 2;
                newCounts[s.substr(0, half)] += pair.second;
                newCounts[s.substr(half, half)] += pair.second;
            }
            else
            {
                newCounts[std::to_string(v * 2024ll)] += pair.second;
            }
        }
        counts = newCounts;
    }
    long long count = 0;
    for (auto &pair : counts)
    {
        count += pair.second;
    }
    return count;
}

long long part1(const std::string &input)
{
    return solve(input, 25);
}

long long part2(const std::string &input)
{
    return solve(input, 75);
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