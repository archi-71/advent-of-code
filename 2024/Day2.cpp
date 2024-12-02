#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (s.substr (pos_start));
    return res;
}

bool isSafe(std::vector<std::string> levels) {
    int dir = 0;
    int prev = -1;
    bool safe = true;
    for (std::string s : levels) {
        int i = atoi(s.c_str());
        if (prev == -1) {
            prev = i;
            continue;
        }
        int dif = i - prev;
        if (dir == 0) {
            dir = dif > 0 ? 1 : -1;
        }
        if (abs(dif) < 1 || abs(dif) > 3 || (i > prev && dir == -1) || (i < prev && dir == 1)) {
            safe = false;
            break;
        }
        prev = i;
    }
    return safe;
}

int part1(const std::vector<std::string> &input)
{
    int count = 0;
    for (std::string line : input) {
        std::vector<std::string> levels = split(line, " ");
        if (isSafe(levels)) {
            count++;
        }
    }
    return count;
}

int part2(const std::vector<std::string> &input)
{
    int count = 0;
    for (std::string line : input) {
        std::vector<std::string> levels = split(line, " ");
        if (isSafe(levels)) {
            count++;
        }
        else {
            for (int i = 0; i < levels.size(); i++) {
                std::vector<std::string> newLevels = levels;
                newLevels.erase(newLevels.begin() + i);
                if (isSafe(newLevels)) {
                    count++;
                    break;
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