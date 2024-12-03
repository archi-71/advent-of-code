#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int part1(const std::vector<std::string> &input)
{
    int total = 0;
    for (std::string line : input)
    {
        int i = 0;
        while (i < line.size() - 7)
        {
            if (line.substr(i, 4) == "mul(")
            {
                i += 4;
                if (isdigit(line[i]))
                {
                    std::string num1 = "";
                    while (isdigit(line[i]))
                    {
                        num1 += line[i];
                        i++;
                    }
                    if (line[i] == ',')
                    {
                        i++;
                        if (isdigit(line[i]))
                        {
                            std::string num2 = "";
                            while (isdigit(line[i]))
                            {
                                num2 += line[i];
                                i++;
                            }
                            if (line[i] == ')')
                            {
                                i++;
                                total += std::stoi(num1) * std::stoi(num2);
                            }
                        }
                    }
                }
            }
            else
            {
                i++;
            }
        }
    }
    return total;
}

int part2(const std::vector<std::string> &input)
{
    int total = 0;
    bool enabled = true;
    for (std::string line : input)
    {
        int i = 0;
        while (i < line.size() - 7)
        {
            if (line.substr(i, 4) == "do()")
            {
                i += 4;
                enabled = true;
            }
            else if (line.substr(i, 7) == "don't()")
            {
                i += 7;
                enabled = false;
            }
            else if (enabled && line.substr(i, 4) == "mul(")
            {
                i += 4;
                if (isdigit(line[i]))
                {
                    std::string num1 = "";
                    while (isdigit(line[i]))
                    {
                        num1 += line[i];
                        i++;
                    }
                    if (line[i] == ',')
                    {
                        i++;
                        if (isdigit(line[i]))
                        {
                            std::string num2 = "";
                            while (isdigit(line[i]))
                            {
                                num2 += line[i];
                                i++;
                            }
                            if (line[i] == ')')
                            {
                                i++;
                                total += std::stoi(num1) * std::stoi(num2);
                            }
                        }
                    }
                }
            }
            else
            {
                i++;
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