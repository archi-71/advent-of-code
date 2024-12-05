#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

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

std::unordered_map<std::string, std::unordered_set<std::string>> map;

bool compare(std::string a, std::string b)
{
    std::unordered_set<std::string> set = map[a];
    return set.find(b) != set.end();
}

int part1(const std::vector<std::string> &input)
{
    map.clear();
    bool rules = true;
    int total = 0;
    for (std::string line : input)
    {
        if (line == "")
        {
            rules = false;
            continue;
        }
        if (rules)
        {
            std::vector<std::string> splitLine = split(line, "|");
            if (map.find(splitLine[0]) != map.end())
            {
                map[splitLine[0]].insert(splitLine[1]);
            }
            else
            {
                std::unordered_set<std::string> vec;
                vec.insert(splitLine[1]);
                map[splitLine[0]] = vec;
            }
        }
        else
        {
            std::vector<std::string> splitLine = split(line, ",");
            std::vector<std::string> s = splitLine;
            std::sort(s.begin(), s.end(), compare);
            if (s == splitLine)
            {
                total += atoi(s[s.size() / 2].c_str());
            }
        }
    }
    return total;
}

int part2(const std::vector<std::string> &input)
{
    map.clear();
    bool rules = true;
    int total = 0;
    for (std::string line : input)
    {
        if (line == "")
        {
            rules = false;
            continue;
        }
        if (rules)
        {
            std::vector<std::string> splitLine = split(line, "|");
            if (map.find(splitLine[0]) != map.end())
            {
                map[splitLine[0]].insert(splitLine[1]);
            }
            else
            {
                std::unordered_set<std::string> vec;
                vec.insert(splitLine[1]);
                map[splitLine[0]] = vec;
            }
        }
        else
        {
            std::vector<std::string> splitLine = split(line, ",");
            std::vector<std::string> s = splitLine;
            std::sort(s.begin(), s.end(), compare);
            if (s != splitLine)
            {
                total += atoi(s[s.size() / 2].c_str());
            }
        }
    }
    return total;
}

int main()
{
    std::ifstream file("input.txt");
    std::vector<std::string> input;
    std::string line;
    while (std::getline(file, line))
    {
        input.push_back(line);
    }
    file.close();

    fprintf(stdout, "Part 1 Answer: %d\n", part1(input));
    fprintf(stdout, "Part 2 Answer: %d\n", part2(input));

    return 0;
}