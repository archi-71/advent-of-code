#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

int part1(const std::vector<std::string> &input)
{
    int x;
    int y;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (input[i][j] == '^')
            {
                x = i;
                y = j;
            }
        }
    }
    int dx = -1;
    int dy = 0;
    std::unordered_set<std::string> set;
    while (x + dx >= 0 && x + dx < input.size() && y + dy >= 0 && y + dy < input[0].size())
    {
        if (input[x + dx][y + dy] == '#')
        {
            int temp = dx;
            dx = dy;
            dy = -temp;
        }
        x += dx;
        y += dy;
        set.insert(std::to_string(x) + "," + std::to_string(y));
    }
    return set.size();
}

int part2(const std::vector<std::string> &input)
{
    int startX;
    int startY;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (input[i][j] == '^')
            {
                startX = i;
                startY = j;
            }
        }
    }
    int x = startX;
    int y = startY;
    int dx = -1;
    int dy = 0;
    std::unordered_set<std::string> path;
    while (x + dx >= 0 && x + dx < input.size() && y + dy >= 0 && y + dy < input[0].size())
    {
        if (input[x + dx][y + dy] == '#')
        {
            int temp = dx;
            dx = dy;
            dy = -temp;
        }
        x += dx;
        y += dy;
        path.insert(std::to_string(x) + "," + std::to_string(y));
    }
    int count = 0;
    for (std::string p : path)
    {
        std::vector<std::string> obstacle = split(p, ",");
        int obstacleX = std::stoi(obstacle[0]);
        int obstacleY = std::stoi(obstacle[1]);
        int x = startX;
        int y = startY;
        int dx = -1;
        int dy = 0;
        std::unordered_set<std::string> set;
        set.insert(std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(dx) + "," + std::to_string(dy));
        bool loop = false;
        while (x + dx >= 0 && x + dx < input.size() && y + dy >= 0 && y + dy < input[0].size())
        {
            if (input[x + dx][y + dy] == '#' || (x + dx == obstacleX && y + dy == obstacleY))
            {
                int temp = dx;
                dx = dy;
                dy = -temp;
            }
            else
            {
                x += dx;
                y += dy;
            }
            std::string key = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(dx) + "," + std::to_string(dy);
            if (set.find(key) != set.end())
            {
                loop = true;
                break;
            }
            set.insert(key);
        }
        if (loop)
        {
            count++;
        }
    }
    return count;
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