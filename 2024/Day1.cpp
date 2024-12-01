#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <map>

int part1(const std::vector<std::string> &input)
{
    std::vector<int> left;
    std::vector<int> right;
    for (std::string line : input)
    {
        std::string str = "";
        for (char c : line)
        {
            if (c == ' ') {
                if (str != "") {
                    left.push_back(std::stoi(str));
                }
                str = "";
            }
            else {
                str += c;
            }
        }
        right.push_back(std::stoi(str));
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int total = 0;
    for (int i; i < left.size(); i++)
    {
        total += abs(left[i] - right[i]);
    }
    return total;
}

int part2(const std::vector<std::string> &input)
{
    std::vector<int> left;
    std::vector<int> right;
    for (std::string line : input)
    {
        std::string str = "";
        for (char c : line)
        {
            if (c == ' ') {
                if (str != "") {
                    left.push_back(std::stoi(str));
                }
                str = "";
            }
            else {
                str += c;
            }
        }
        right.push_back(std::stoi(str));
    }
    std::map<int, int> freq;
    for (int r : right)
    {
        freq[r]++;
    }
    int total = 0;
    for (int l : left)
    {
        total += l * freq[l];
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