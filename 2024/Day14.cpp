#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>
#include <thread>

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
    const int width = 101;
    const int height = 103;
    const int t = 100;
    int topLeft = 0;
    int topRight = 0;
    int bottomLeft = 0;
    int bottomRight = 0;
    for (std::string line : input)
    {
        std::vector<std::string> splitLine = split(line, " ");
        std::vector<std::string> splitPos = split(split(splitLine[0], "=")[1], ",");
        std::vector<std::string> splitVel = split(split(splitLine[1], "=")[1], ",");
        int x = atoi(splitPos[0].c_str());
        int y = atoi(splitPos[1].c_str());
        int dx = atoi(splitVel[0].c_str());
        int dy = atoi(splitVel[1].c_str());

        int X = (x + t * dx) % width;
        if (X < 0)
        {
            X += width;
        }
        int Y = (y + t * dy) % height;
        if (Y < 0)
        {
            Y += height;
        }

        if (X < width / 2 && Y < height / 2)
        {
            topLeft++;
        }
        else if (X > width / 2 && Y < height / 2)
        {
            topRight++;
        }
        else if (X < width / 2 && Y > height / 2)
        {
            bottomLeft++;
        }
        else if (X > width / 2 && Y > height / 2)
        {
            bottomRight++;
        }
    }
    return topLeft * topRight * bottomLeft * bottomRight;
}

int part2(const std::vector<std::string> &input)
{
    const int width = 101;
    const int height = 103;
    int t = 0;
    while (true)
    {
        std::unordered_set<int> positions;
        for (std::string line : input)
        {
            std::vector<std::string> splitLine = split(line, " ");
            std::vector<std::string> splitPos = split(split(splitLine[0], "=")[1], ",");
            std::vector<std::string> splitVel = split(split(splitLine[1], "=")[1], ",");
            int x = atoi(splitPos[0].c_str());
            int y = atoi(splitPos[1].c_str());
            int dx = atoi(splitVel[0].c_str());
            int dy = atoi(splitVel[1].c_str());

            int X = (x + t * dx) % width;
            if (X < 0)
            {
                X += width;
            }
            int Y = (y + t * dy) % height;
            if (Y < 0)
            {
                Y += height;
            }
            positions.insert(Y * width + X);
        }
        bool tree = false;
        int line = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (positions.find(i * width + j) != positions.end())
                {
                    line++;
                    if (line > 10)
                    {
                        return t;
                    }
                }
                else
                {
                    line = 0;
                }
            }
        }
        t++;
    }
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