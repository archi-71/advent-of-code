#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

bool solvable1(long test, std::vector<long> &values)
{
    long val = values.back();
    values.pop_back();
    if (values.empty())
    {
        values.push_back(val);
        return test == val;
    }
    if (test % val == 0 && solvable1(test / val, values))
    {
        return true;
    }
    if (test - val >= 0 && solvable1(test - val, values))
    {
        return true;
    }
    values.push_back(val);
    return false;
}

long part1(const std::vector<std::string> &input)
{
    long total = 0;
    for (const auto &line : input)
    {
        std::vector<std::string> parts = split(line, " ");
        long test = std::stol(parts[0]);
        std::vector<long> values;
        for (int i = 1; i < parts.size(); i++)
        {
            values.push_back(std::stol(parts[i]));
        }
        if (solvable1(test, values))
        {
            total += test;
        }
    }
    return total;
}

bool hasSuffix(const std::string &str, const std::string &suffix)
{
    return str.size() > suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool solvable2(long test, std::vector<long> &values)
{
    long val = values.back();
    values.pop_back();
    if (values.empty())
    {
        values.push_back(val);
        return test == val;
    }
    std::string testStr = std::to_string(test);
    std::string valStr = std::to_string(val);
    if (hasSuffix(testStr, valStr) && solvable2(std::stol(testStr.substr(0, testStr.size() - valStr.size())), values))
    {
        return true;
    }
    if (test % val == 0 && solvable2(test / val, values))
    {
        return true;
    }
    if (test - val >= 0 && solvable2(test - val, values))
    {
        return true;
    }
    values.push_back(val);
    return false;
}

long part2(const std::vector<std::string> &input)
{
    long total = 0;
    for (const auto &line : input)
    {
        std::vector<std::string> parts = split(line, " ");
        long test = std::stol(parts[0]);
        std::vector<long> values;
        for (int i = 1; i < parts.size(); i++)
        {
            values.push_back(std::stol(parts[i]));
        }
        if (solvable2(test, values))
        {
            total += test;
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

    fprintf(stdout, "Part 1 Answer: %ld\n", part1(input));
    fprintf(stdout, "Part 2 Answer: %ld\n", part2(input));

    return 0;
}