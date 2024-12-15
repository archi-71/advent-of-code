#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

int part1(const std::vector<std::string> &input)
{
    std::vector<std::vector<char>> map;
    int x, y;
    int i = 0;
    while (input[i].size() > 0)
    {
        map.push_back(std::vector<char>(input[i].size()));
        for (int j = 0; j < input[i].size(); j++)
        {
            map[i][j] = input[i][j];
            if (input[i][j] == '@')
            {
                x = i;
                y = j;
            }
        }
        i++;
    }
    i++;
    while (i < input.size())
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            int dx;
            int dy;
            switch (input[i][j])
            {
            case '^':
                dx = -1;
                dy = 0;
                break;
            case 'v':
                dx = 1;
                dy = 0;
                break;
            case '<':
                dx = 0;
                dy = -1;
                break;
            case '>':
                dx = 0;
                dy = 1;
                break;
            }
            int k = 1;
            while (map[x + dx * k][y + dy * k] == 'O')
            {
                k++;
            }
            if (map[x + dx * k][y + dy * k] == '#')
            {
                continue;
            }
            for (int l = k; l > 0; l--)
            {
                map[x + dx * l][y + dy * l] = map[x + dx * (l - 1)][y + dy * (l - 1)];
            }
            map[x][y] = '.';
            x += dx;
            y += dy;
        }
        i++;
    }
    int total = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 'O')
            {
                total += 100 * i + j;
            }
        }
    }
    return total;
}

int part2(const std::vector<std::string> &input)
{
    std::vector<std::vector<char>> map;
    int x, y;
    int i = 0;
    while (input[i].size() > 0)
    {
        map.push_back(std::vector<char>(input[i].size() * 2));
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == 'O')
            {
                map[i][2 * j] = '[';
                map[i][2 * j + 1] = ']';
            }
            else if (input[i][j] == '@')
            {
                map[i][2 * j] = '@';
                map[i][2 * j + 1] = '.';
                x = i;
                y = 2 * j;
            }
            else
            {
                map[i][2 * j] = input[i][j];
                map[i][2 * j + 1] = input[i][j];
            }
        }
        i++;
    }
    i++;
    while (i < input.size())
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            int dx;
            int dy;
            switch (input[i][j])
            {
            case '^':
                dx = -1;
                dy = 0;
                break;
            case 'v':
                dx = 1;
                dy = 0;
                break;
            case '<':
                dx = 0;
                dy = -1;
                break;
            case '>':
                dx = 0;
                dy = 1;
                break;
            }
            if (dx == 0)
            {
                int k = 1;
                while (map[x][y + dy * k] == '[' || map[x][y + dy * k] == ']')
                {
                    k++;
                }
                if (map[x][y + dy * k] == '#')
                {
                    continue;
                }
                for (int l = k; l > 0; l--)
                {
                    map[x][y + dy * l] = map[x][y + dy * (l - 1)];
                }
                map[x][y] = '.';
            }
            else
            {
                std::vector<std::unordered_set<int>> yVals = {{y}};
                int k = 0;
                bool stop;
                bool blocked = false;
                do
                {
                    k++;
                    stop = true;
                    std::unordered_set<int> set;
                    for (int yVal : yVals.back())
                    {
                        if (map[x + dx * k][yVal] == '#')
                        {
                            stop = blocked = true;
                            break;
                        }
                        else if (map[x + dx * k][yVal] == '[')
                        {
                            stop = false;
                            set.insert(yVal);
                            set.insert(yVal + 1);
                        }
                        else if (map[x + dx * k][yVal] == ']')
                        {
                            stop = false;
                            set.insert(yVal - 1);
                            set.insert(yVal);
                        }
                    }
                    yVals.push_back(set);
                } while (!stop);
                if (blocked)
                {
                    continue;
                }
                for (int l = k; l > 0; l--)
                {
                    for (int yVal : yVals[l - 1])
                    {
                        map[x + dx * l][yVal] = map[x + dx * (l - 1)][yVal];
                        map[x + dx * (l - 1)][yVal] = '.';
                    }
                }
            }
            x += dx;
            y += dy;
        }
        i++;
    }
    int total = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == '[')
            {
                total += 100 * i + j;
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