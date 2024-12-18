#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

struct Vec2
{
    int x;
    int y;

    bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Vec2Hash
{
    std::size_t operator()(const Vec2 &coord) const
    {
        return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
    }
};

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

int shortestPath(Vec2 start, Vec2 end, std::unordered_set<Vec2, Vec2Hash> corrupted, int gridSize)
{
    std::unordered_set<Vec2, Vec2Hash> visited;
    std::unordered_map<Vec2, int, Vec2Hash> steps;
    steps[start] = 1;
    std::queue<Vec2> frontier;
    frontier.push(start);
    while (!frontier.empty())
    {
        Vec2 current = frontier.front();
        frontier.pop();
        if (current == end)
        {
            return steps[current] - 1;
        }
        if (visited.find(current) != visited.end())
        {
            continue;
        }
        visited.insert(current);
        for (int i = -1; i <= 1; i += 2)
        {
            Vec2 neighbour = {current.x + i, current.y};
            if (neighbour.x < 0 || neighbour.x >= gridSize || corrupted.find(neighbour) != corrupted.end())
            {
                continue;
            }
            steps[neighbour] = steps[current] + 1;
            frontier.push(neighbour);
        }
        for (int i = -1; i <= 1; i += 2)
        {
            Vec2 neighbour = {current.x, current.y + i};
            if (neighbour.y < 0 || neighbour.y >= gridSize || corrupted.find(neighbour) != corrupted.end())
            {
                continue;
            }
            steps[neighbour] = steps[current] + 1;
            frontier.push(neighbour);
        }
    }
    return -1;
}

int part1(const std::vector<std::string> &input)
{
    int gridSize = 71;
    int bytes = 1024;
    std::unordered_set<Vec2, Vec2Hash> corrupted;
    for (int i = 0; i < bytes; i++)
    {
        std::string line = input[i];
        for (int i = 0; i < line.size(); i++)
        {
            std::vector<std::string> splitLine = split(line, ",");
            Vec2 pos = {atoi(splitLine[0].c_str()), atoi(splitLine[1].c_str())};
            corrupted.insert(pos);
        }
    }
    Vec2 start = {0, 0};
    Vec2 end = {gridSize - 1, gridSize - 1};
    return shortestPath(start, end, corrupted, gridSize);
}

std::string part2(const std::vector<std::string> &input)
{
    int gridSize = 71;
    int left = 0;
    int right = input.size() - 1;
    while (left <= right)
    {
        int bytes = (left + right) / 2;
        std::unordered_set<Vec2, Vec2Hash> corrupted;
        for (int i = 0; i < bytes; i++)
        {
            std::string line = input[i];
            std::vector<std::string> splitLine = split(line, ",");
            Vec2 pos = {atoi(splitLine[0].c_str()), atoi(splitLine[1].c_str())};
            corrupted.insert(pos);
        }
        Vec2 start = {0, 0};
        Vec2 end = {gridSize - 1, gridSize - 1};
        bool reachable = shortestPath(start, end, corrupted, gridSize) != -1;
        if (reachable)
        {
            left = bytes + 1;
        }
        else
        {
            right = bytes - 1;
        }
    }
    return input[right];
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
    fprintf(stdout, "Part 2 Answer: %s\n", part2(input).c_str());

    return 0;
}