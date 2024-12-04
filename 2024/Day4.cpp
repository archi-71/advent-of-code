#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int part1(const std::vector<std::string> &input)
{
    int count = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == 'X')
            {
                for (int x = -1; x <= 1; x++)
                {
                    for (int y = -1; y <= 1; y++)
                    {
                        if (x == 0 && y == 0)
                        {
                            continue;
                        }
                        if (i + 3 * x < 0 || i + 3 * x >= input.size() || j + 3 * y < 0 || j + 3 * y >= input[i].size())
                        {
                            continue;
                        }
                        if (input[i + x][j + y] == 'M' && input[i + 2 * x][j + 2 * y] == 'A' && input[i + 3 * x][j + 3 * y] == 'S')
                        {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}

int part2(const std::vector<std::string> &input)
{
    int count = 0;
    for (int i = 1; i < input.size() - 1; i++)
    {
        for (int j = 1; j < input[i].size() - 1; j++)
        {
            if (input[i][j] == 'A')
            {
                if (input[i + 1][j + 1] == 'M' && input[i - 1][j - 1] == 'S' || input[i + 1][j + 1] == 'S' && input[i - 1][j - 1] == 'M')
                {
                    if (input[i + 1][j - 1] == 'M' && input[i - 1][j + 1] == 'S' || input[i + 1][j - 1] == 'S' && input[i - 1][j + 1] == 'M')
                    {
                        count++;
                    }
                }
            }
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