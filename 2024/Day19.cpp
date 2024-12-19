#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

class Trie
{
    Trie *children[5];
    bool isWord = false;

    int charToIndex(char c)
    {
        switch (c)
        {
        case 'w':
            return 0;
        case 'u':
            return 1;
        case 'b':
            return 2;
        case 'r':
            return 3;
        case 'g':
            return 4;
        }
        return -1;
    }

public:
    void insert(std::string s)
    {
        Trie *node = this;
        for (char c : s)
        {
            int index = charToIndex(c);
            if (node->children[index] == nullptr)
            {
                node->children[index] = new Trie();
            }
            node = node->children[index];
        }
        node->isWord = true;
    }

    std::vector<int> search(std::string s)
    {
        std::vector<int> prefixes;
        Trie *node = this;
        for (int i = 0; i < s.length(); i++)
        {
            int index = charToIndex(s[i]);
            if (node->children[index] == nullptr)
            {
                return prefixes;
            }
            node = node->children[index];
            if (node->isWord)
            {
                prefixes.push_back(i + 1);
            }
        }
        return prefixes;
    }
};

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
    Trie *root = new Trie();
    for (std::string towel : split(input[0], ", "))
    {
        root->insert(towel);
    }
    int count = 0;
    for (int i = 2; i < input.size(); i++)
    {
        std::string design = input[i];
        std::vector<bool> possible(design.length() + 1, false);
        possible[0] = true;
        for (int j = 0; j < design.length(); j++)
        {
            if (!possible[j])
            {
                continue;
            }
            std::vector<int> towels = root->search(design.substr(j, design.length() - j));
            for (int t : towels)
            {
                possible[j + t] = true;
            }
        }
        count += possible[design.length()];
    }
    return count;
}

long long part2(const std::vector<std::string> &input)
{
    Trie *root = new Trie();
    for (std::string towel : split(input[0], ", "))
    {
        root->insert(towel);
    }
    long long total = 0;
    for (int i = 2; i < input.size(); i++)
    {
        std::string design = input[i];
        std::vector<long long> ways(design.length() + 1, 0);
        ways[0] = 1;
        for (int j = 0; j < design.length(); j++)
        {
            if (ways[j] == 0)
            {
                continue;
            }
            std::vector<int> towels = root->search(design.substr(j, design.length() - j));
            for (int t : towels)
            {
                ways[j + t] += ways[j];
            }
        }
        total += ways[design.length()];
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