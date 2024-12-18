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

long long reg[3];

long long combo(int op)
{
    switch (op)
    {
    case 4:
        return reg[0];
    case 5:
        return reg[1];
    case 6:
        return reg[2];
    default:
        return op;
    }
}

int ptr;

int step(std::vector<int> &program)
{
    int output = -1;
    int opcode = program[ptr];
    int operand = program[ptr + 1];
    switch (opcode)
    {
    case 0:
        reg[0] = reg[0] >> combo(operand);
        ptr += 2;
        break;
    case 1:
        reg[1] = reg[1] ^ operand;
        ptr += 2;
        break;
    case 2:
        reg[1] = combo(operand) % 8;
        ptr += 2;
        break;
    case 3:
        if (reg[0] != 0)
        {
            ptr = operand;
        }
        else
        {
            ptr += 2;
        }
        break;
    case 4:
        reg[1] = reg[1] ^ reg[2];
        ptr += 2;
        break;
    case 5:
        output = combo(operand) % 8;
        ptr += 2;
        break;
    case 6:
        reg[1] = reg[0] >> combo(operand);
        ptr += 2;
        break;
    case 7:
        reg[2] = reg[0] >> combo(operand);
        ptr += 2;
        break;
    }
    return output;
}

std::string part1(const std::vector<std::string> &input)
{
    std::vector<int> program;
    std::string programStr = split(input[4], " ")[1];
    std::vector<std::string> programSplit = split(programStr, ",");
    for (std::string s : programSplit)
    {
        program.push_back(atoi(s.c_str()));
    }
    for (int i = 0; i < 3; i++)
    {
        reg[i] = std::stoll(input[i].substr(12, input[i].size() - 12).c_str());
    }
    std::string output;
    ptr = 0;
    while (ptr < program.size())
    {
        int out = step(program);
        if (out != -1)
        {
            if (output.size() > 0)
            {
                output += ",";
            }
            output += std::to_string(out);
        }
    }
    return output;
}

long long part2(const std::vector<std::string> &input)
{
    std::vector<int> program;
    std::string programStr = split(input[4], " ")[1];
    std::vector<std::string> programSplit = split(programStr, ",");
    for (std::string s : programSplit)
    {
        program.push_back(atoi(s.c_str()));
    }
    std::vector<long long> A(program.size(), 0);
    int i = 0;
    while (i < A.size())
    {
        bool found = false;
        for (long long a = A[i]; a < 8ll; a++)
        {
            reg[0] = 0;
            for (int j = 0; j < A.size(); j++)
            {
                reg[0] += ((i == j ? a : A[j]) << ((A.size() - j - 1) * 3));
            }
            for (int j = 1; j < 3; j++)
            {
                reg[j] = std::stoll(input[j].substr(12, input[j].size() - 12).c_str());
            }
            int outNum = 0;
            ptr = 0;
            while (ptr < program.size())
            {
                int output = step(program);
                if (output != -1)
                {
                    outNum++;
                    if (outNum == A.size() - i)
                    {
                        if (output == program[outNum - 1])
                        {
                            found = true;
                        }
                        break;
                    }
                }
            }
            if (found)
            {
                A[i] = a;
                break;
            }
        };
        if (found)
        {
            i++;
        }
        else
        {
            A[i] = 0;
            i--;
            if (i < 0)
            {
                break;
            }
            A[i]++;
        }
    }
    reg[0] = 0;
    for (int j = 0; j < A.size(); j++)
    {
        reg[0] += (A[j] << ((A.size() - j - 1) * 3));
    }
    return reg[0];
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

    fprintf(stdout, "Part 1 Answer: %s\n", part1(input).c_str());
    fprintf(stdout, "Part 2 Answer: %lld\n", part2(input));

    return 0;
}