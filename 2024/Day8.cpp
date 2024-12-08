#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Vec2
{
    int x;
    int y;

    bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }

    Vec2 operator+(const Vec2 &other) const
    {
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2 &other) const
    {
        return {x - other.x, y - other.y};
    }
};

struct Vec2Hash
{
    std::size_t operator()(const Vec2 &coord) const
    {
        return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
    }
};

int part1(const std::vector<std::string> &input)
{
    std::unordered_map<char, std::vector<Vec2>> antennae;
    std::unordered_set<Vec2, Vec2Hash> antinodes;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            char c = input[i][j];
            if (c != '.')
            {
                Vec2 coord = {i, j};
                if (antennae.find(c) != antennae.end())
                {
                    for (Vec2 a : antennae[c])
                    {
                        Vec2 diff = a - coord;
                        Vec2 antinode1 = a + diff;
                        if (antinode1.x >= 0 && antinode1.x < input.size() && antinode1.y >= 0 && antinode1.y < input[0].size())
                        {
                            antinodes.insert(antinode1);
                        }
                        Vec2 antinode2 = coord - diff;
                        if (antinode2.x >= 0 && antinode2.x < input.size() && antinode2.y >= 0 && antinode2.y < input[0].size())
                        {
                            antinodes.insert(antinode2);
                        }
                    }
                    antennae[c].push_back(coord);
                }
                else
                {
                    antennae[c] = {coord};
                }
            }
        }
    }
    return antinodes.size();
}

int part2(const std::vector<std::string> &input)
{
    std::unordered_map<char, std::vector<Vec2>> antennae;
    std::unordered_set<Vec2, Vec2Hash> antinodes;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            char c = input[i][j];
            if (c != '.')
            {
                Vec2 coord = {i, j};
                if (antennae.find(c) != antennae.end())
                {
                    for (Vec2 a : antennae[c])
                    {
                        Vec2 diff = a - coord;
                        Vec2 antinode1 = a;
                        while (antinode1.x >= 0 && antinode1.x < input.size() && antinode1.y >= 0 && antinode1.y < input[0].size())
                        {
                            antinodes.insert(antinode1);
                            antinode1 = antinode1 + diff;
                        }
                        Vec2 antinode2 = coord;
                        while (antinode2.x >= 0 && antinode2.x < input.size() && antinode2.y >= 0 && antinode2.y < input[0].size())
                        {
                            antinodes.insert(antinode2);
                            antinode2 = antinode2 - diff;
                        }
                    }
                    antennae[c].push_back(coord);
                }
                else
                {
                    antennae[c] = {coord};
                }
            }
        }
    }
    return antinodes.size();
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