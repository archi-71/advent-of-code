#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

int part1(const std::vector<std::string> &input)
{
    int scores = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '0')
            {
                std::unordered_set<int> visited;
                std::vector<int> frontier;
                frontier.push_back(i * input[i].size() + j);
                while (!frontier.empty())
                {
                    int current = frontier.back();
                    frontier.pop_back();
                    if (visited.find(current) != visited.end())
                    {
                        continue;
                    }
                    visited.insert(current);
                    int x = current / input[i].size();
                    int y = current % input[i].size();
                    int height = input[x][y] - '0';
                    if (height == 9)
                    {
                        scores++;
                        continue;
                    }
                    for (int k = -1; k <= 1; k++)
                    {
                        if (x + k < 0 || x + k >= input.size())
                        {
                            continue;
                        }
                        if (input[x + k][y] - '0' == height + 1)
                        {
                            frontier.push_back((x + k) * input[i].size() + y);
                        }
                    }
                    for (int k = -1; k <= 1; k++)
                    {
                        if (y + k < 0 || y + k >= input[i].size())
                        {
                            continue;
                        }
                        if (input[x][y + k] - '0' == height + 1)
                        {
                            frontier.push_back(x * input[i].size() + y + k);
                        }
                    }
                }
            }
        }
    }
    return scores;
}

int part2(const std::vector<std::string> &input)
{
    int scores = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '0')
            {
                std::vector<int> frontier;
                frontier.push_back(i * input[i].size() + j);
                while (!frontier.empty())
                {
                    int current = frontier.back();
                    frontier.pop_back();
                    int x = current / input[i].size();
                    int y = current % input[i].size();
                    int height = input[x][y] - '0';
                    if (height == 9)
                    {
                        scores++;
                        continue;
                    }
                    for (int k = -1; k <= 1; k++)
                    {
                        if (x + k < 0 || x + k >= input.size())
                        {
                            continue;
                        }
                        if (input[x + k][y] - '0' == height + 1)
                        {
                            frontier.push_back((x + k) * input[i].size() + y);
                        }
                    }
                    for (int k = -1; k <= 1; k++)
                    {
                        if (y + k < 0 || y + k >= input[i].size())
                        {
                            continue;
                        }
                        if (input[x][y + k] - '0' == height + 1)
                        {
                            frontier.push_back(x * input[i].size() + y + k);
                        }
                    }
                }
            }
        }
    }
    return scores;
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