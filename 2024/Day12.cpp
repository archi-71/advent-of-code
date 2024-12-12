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

int part1(const std::vector<std::string> &input)
{
    int price = 0;
    std::unordered_set<std::string> visited;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (visited.find(std::to_string(i) + "," + std::to_string(j)) != visited.end())
            {
                continue;
            }
            char c = input[i][j];
            std::vector<std::string> frontier;
            frontier.push_back(std::to_string(i) + "," + std::to_string(j));
            int area = 0;
            int perimeter = 0;
            while (frontier.size() > 0)
            {
                std::string current = frontier.back();
                frontier.pop_back();
                if (visited.find(current) != visited.end())
                {
                    continue;
                }
                visited.insert(current);
                std::vector<std::string> splits = split(current, ",");
                int x = std::stoi(splits[0]);
                int y = std::stoi(splits[1]);
                area++;
                for (int k = -1; k <= 1; k += 2)
                {
                    if (x + k < 0 || x + k >= input.size() || input[x + k][y] != c)
                    {
                        perimeter++;
                    }
                    else
                    {
                        frontier.push_back(std::to_string(x + k) + "," + std::to_string(y));
                    }
                }
                for (int k = -1; k <= 1; k += 2)
                {
                    if (y + k < 0 || y + k >= input[0].size() || input[x][y + k] != c)
                    {
                        perimeter++;
                    }
                    else
                    {
                        frontier.push_back(std::to_string(x) + "," + std::to_string(y + k));
                    }
                }
            }
            price += area * perimeter;
        }
    }
    return price;
}

int part2(const std::vector<std::string> &input)
{
    int price = 0;
    std::unordered_set<std::string> visited;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (visited.find(std::to_string(i) + "," + std::to_string(j)) != visited.end())
            {
                continue;
            }
            char c = input[i][j];
            std::vector<std::string> frontier;
            frontier.push_back(std::to_string(i) + "," + std::to_string(j));
            int area = 0;
            int sides = 0;
            std::unordered_map<std::string, std::unordered_set<std::string>> perimeter;
            while (frontier.size() > 0)
            {
                std::string current = frontier.back();
                frontier.pop_back();
                if (visited.find(current) != visited.end())
                {
                    continue;
                }
                visited.insert(current);
                std::vector<std::string> splits = split(current, ",");
                int x = std::stoi(splits[0]);
                int y = std::stoi(splits[1]);
                area++;
                for (int k = -1; k <= 1; k += 2)
                {
                    if (x + k < 0 || x + k >= input.size() || input[x + k][y] != c)
                    {
                        std::string pos = std::to_string(x + k) + "," + std::to_string(y);
                        std::string dir = std::to_string(k) + ",0";
                        if (perimeter.find(pos) != perimeter.end())
                        {
                            perimeter[pos].insert(dir);
                        }
                        else
                        {
                            perimeter[pos] = {dir};
                        }
                        bool newSide = true;
                        for (int l = -1; l <= 1; l += 2)
                        {
                            std::string adjPos = std::to_string(x + k + l) + "," + std::to_string(y);
                            if (perimeter.find(adjPos) != perimeter.end() && perimeter[adjPos].find(dir) != perimeter[adjPos].end())
                            {
                                newSide = false;
                                break;
                            }
                        }
                        for (int l = -1; l <= 1; l += 2)
                        {
                            std::string adjPos = std::to_string(x + k) + "," + std::to_string(y + l);
                            if (perimeter.find(adjPos) != perimeter.end() && perimeter[adjPos].find(dir) != perimeter[adjPos].end())
                            {
                                newSide = false;
                                break;
                            }
                        }
                        if (newSide)
                        {
                            sides += 2;
                        }
                    }
                    else
                    {
                        frontier.push_back(std::to_string(x + k) + "," + std::to_string(y));
                    }
                }
                for (int k = -1; k <= 1; k += 2)
                {
                    if (y + k < 0 || y + k >= input[0].size() || input[x][y + k] != c)
                    {
                        std::string pos = std::to_string(x) + "," + std::to_string(y + k);
                        std::string dir = "0," + std::to_string(k);
                        if (perimeter.find(pos) != perimeter.end())
                        {
                            perimeter[pos].insert(dir);
                        }
                        else
                        {
                            perimeter[pos] = {dir};
                        }
                        bool newSide = false;
                        for (int l = -1; l <= 1; l += 2)
                        {
                            std::string adjPos = std::to_string(x + l) + "," + std::to_string(y + k);
                            if (perimeter.find(adjPos) != perimeter.end() && perimeter[adjPos].find(dir) != perimeter[adjPos].end())
                            {
                                newSide = false;
                                break;
                            }
                        }
                        for (int l = -1; l <= 1; l += 2)
                        {
                            std::string adjPos = std::to_string(x) + "," + std::to_string(y + k + l);
                            if (perimeter.find(adjPos) != perimeter.end() && perimeter[adjPos].find(dir) != perimeter[adjPos].end())
                            {
                                newSide = false;
                                break;
                            }
                        }
                        if (newSide)
                        {
                            sides += 2;
                        }
                    }
                    else
                    {
                        frontier.push_back(std::to_string(x) + "," + std::to_string(y + k));
                    }
                }
            }
            price += area * sides;
        }
    }
    return price;
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