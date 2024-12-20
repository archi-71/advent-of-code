#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct Vec2
{
    int x;
    int y;

    bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2 &other) const
    {
        return x != other.x || y != other.y;
    }
};

struct Vec2Hash
{
    std::size_t operator()(const Vec2 &coord) const
    {
        return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
    }
};

int solve(const std::vector<std::string> &input, const int maxCheat)
{
    Vec2 start;
    Vec2 end;
    std::vector<std::vector<char>> map(input.size(), std::vector<char>(input[0].size()));
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            map[i][j] = input[i][j];
            if (input[i][j] == 'S')
            {
                start = {i, j};
            }
            else if (input[i][j] == 'E')
            {
                end = {i, j};
            }
        }
    }
    std::unordered_map<Vec2, int, Vec2Hash> times;
    times[start] = 0;
    Vec2 prev = Vec2{-1, -1};
    Vec2 current = start;
    while (current != end)
    {
        bool found = false;
        for (int i = -1; i <= 1; i += 2)
        {
            Vec2 next = Vec2{current.x + i, current.y};
            if (map[next.x][next.y] != '#' && next != prev)
            {
                times[next] = times[current] + 1;
                prev = current;
                current = next;
                found = true;
                break;
            }
        }
        if (found)
        {
            continue;
        }
        for (int i = -1; i <= 1; i += 2)
        {
            Vec2 next = Vec2{current.x, current.y + i};
            if (map[next.x][next.y] != '#' && next != prev)
            {
                times[next] = times[current] + 1;
                prev = current;
                current = next;
                break;
            }
        }
    }
    int count = 0;
    std::unordered_set<std::string> cheats;
    for (const auto &pair : times)
    {
        Vec2 start = pair.first;
        for (int i = -maxCheat; i <= maxCheat; i += 1)
        {
            for (int j = -maxCheat; j <= maxCheat; j += 1)
            {
                int length = abs(i) + abs(j);
                if (i == 0 && j == 0 || length > maxCheat)
                {
                    continue;
                }
                Vec2 end = {start.x + i, start.y + j};
                if (end.x < 0 || end.x >= map.size() || end.y < 0 || end.y >= map[0].size() || map[end.x][end.y] == '#')
                {
                    continue;
                }
                std::string cheat = std::to_string(start.x) + " " + std::to_string(start.y) + " " + std::to_string(end.x) + " " + std::to_string(end.y);
                if (cheats.find(cheat) != cheats.end())
                {
                    continue;
                }
                cheats.insert(cheat);
                if (times[end] - times[start] - length >= 100)
                {
                    count++;
                }
            }
        }
    }
    return count++;
}

int part1(const std::vector<std::string> &input)
{
    return solve(input, 2);
}

int part2(const std::vector<std::string> &input)
{
    return solve(input, 20);
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