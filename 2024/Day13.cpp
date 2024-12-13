#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    int total = 0;
    int i = 0;
    while (i < input.size())
    {
        std::vector<std::string> A = split(input[i], "+");
        int Ax = atoi(A[1].c_str());
        int Ay = atoi(A[2].c_str());
        std::vector<std::string> B = split(input[i + 1], "+");
        int Bx = atoi(B[1].c_str());
        int By = atoi(B[2].c_str());
        std::vector<std::string> prize = split(input[i + 2], "=");
        int Px = atoi(prize[1].c_str());
        int Py = atoi(prize[2].c_str());
        i += 4;

        int a = -(By * Px - Py * Bx) / (Ay * Bx - By * Ax);
        int b = (Px - Ax * a) / Bx;
        if (a < 0 || a > 100 || b < 0 || b > 100 || (Ax * a + Bx * b != Px) || (Ay * a + By * b != Py))
        {
            continue;
        }
        total += a * 3 + b;
    }
    return total;
}

long long part2(const std::vector<std::string> &input)
{
    long long total = 0;
    int i = 0;
    while (i < input.size())
    {
        std::vector<std::string> A = split(input[i], "+");
        long long Ax = std::stoll(A[1]);
        long long Ay = std::stoll(A[2]);
        std::vector<std::string> B = split(input[i + 1], "+");
        long long Bx = std::stoll(B[1]);
        long long By = std::stoll(B[2]);
        std::vector<std::string> prize = split(input[i + 2], "=");
        long long Px = std::stoll(prize[1]) + 10000000000000;
        long long Py = std::stoll(prize[2]) + 10000000000000;
        i += 4;

        long long a = -(By * Px - Py * Bx) / (Ay * Bx - By * Ax);
        long long b = (Px - Ax * a) / Bx;
        if (a < 0 || b < 0 || (Ax * a + Bx * b != Px) || (Ay * a + By * b != Py))
        {
            continue;
        }
        total += a * 3 + b;
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
    fprintf(stdout, "Part 2 Answer: %lld\n", part2(input));

    return 0;
}