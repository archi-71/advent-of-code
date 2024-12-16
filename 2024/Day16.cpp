#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct Vec2
{
    int x;
    int y;

    bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }

    Vec2 operator-(const Vec2 &other) const
    {
        return {x - other.x, y - other.y};
    }
};

struct Vec2Hash
{
    std::size_t operator()(const Vec2 &coord) const
    {
        return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
    }
};

std::unordered_map<Vec2, int, Vec2Hash> scores;

bool CompareVec(Vec2 a, Vec2 b)
{
    return scores[a] > scores[b];
}

int part1(const std::vector<std::string> &input)
{
    Vec2 start;
    Vec2 end;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (input[i][j] == 'S')
            {
                start = {i, j};
            }
            else if (input[i][j] == 'E')
            {
                end = {i, j};
            }
        }
    }
    std::unordered_set<Vec2, Vec2Hash> visited;
    std::priority_queue<Vec2, std::vector<Vec2>, std::function<bool(Vec2, Vec2)>> frontier(CompareVec);
    frontier.push(start);
    std::unordered_map<Vec2, Vec2, Vec2Hash> direction;
    direction[start] = {0, 1};
    scores[start] = 0;
    while (!frontier.empty())
    {
        Vec2 current = frontier.top();
        frontier.pop();
        if (current == end)
        {
            return scores[current];
        }
        visited.insert(current);
        Vec2 dir = direction[current];
        for (int i = -1; i <= 1; i++)
        {
            Vec2 newDir = i == 0 ? dir : Vec2{dir.y * i, dir.x * -i};
            Vec2 neighbour = {current.x + newDir.x, current.y + newDir.y};
            if (visited.find(neighbour) != visited.end())
            {
                continue;
            }
            if (input[neighbour.x][neighbour.y] != '#')
            {
                direction[neighbour] = newDir;
                scores[neighbour] = scores[current] + 1 + abs(i) * 1000;
                frontier.push(neighbour);
            }
        }
    }
    return -1;
}

struct Node
{
    Vec2 pos;
    Vec2 dir;

    bool operator==(const Node &other) const
    {
        return pos == other.pos && dir == other.dir;
    }
};

struct NodeHash
{
    std::size_t operator()(const Node &coord) const
    {
        return std::hash<int>()(coord.pos.x) ^ (std::hash<int>()(coord.pos.y) << 1 ^ (std::hash<int>()(coord.dir.x) << 2) ^ (std::hash<int>()(coord.dir.y) << 3));
    }
};

std::unordered_map<Node, int, NodeHash> bestScores;

bool CompareNode(Node a, Node b)
{
    return bestScores[a] > bestScores[b];
}

int part2(const std::vector<std::string> &input)
{
    Vec2 start;
    Vec2 end;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].size(); j++)
        {
            if (input[i][j] == 'S')
            {
                start = {i, j};
            }
            else if (input[i][j] == 'E')
            {
                end = {i, j};
            }
        }
    }
    std::priority_queue<Node, std::vector<Node>, std::function<bool(Node, Node)>> frontier(CompareNode);
    frontier.push({start, {0, 1}});
    bestScores[{start, {0, 1}}] = 0;
    std::unordered_map<Node, std::vector<std::vector<Vec2>>, NodeHash> bestPaths;
    bestPaths[{start, {0, 1}}] = {{start}};
    while (!frontier.empty())
    {
        Node current = frontier.top();
        frontier.pop();
        if (current.pos == end)
        {
            continue;
        }
        for (int i = -1; i <= 1; i++)
        {
            Vec2 newDir = i == 0 ? current.dir : Vec2{current.dir.y * i, current.dir.x * -i};
            Node neighbour = {{current.pos.x + newDir.x, current.pos.y + newDir.y}, newDir};
            if (input[neighbour.pos.x][neighbour.pos.y] != '#')
            {
                int newScore = bestScores[current] + 1 + abs(i) * 1000;
                if (bestScores.find(neighbour) != bestScores.end())
                {
                    if (newScore < bestScores[neighbour])
                    {
                        bestScores[neighbour] = newScore;
                        std::vector<std::vector<Vec2>> newBestPaths;
                        for (std::vector<Vec2> path : bestPaths[current])
                        {
                            std::vector<Vec2> newPath = path;
                            newPath.push_back(neighbour.pos);
                            newBestPaths.push_back(newPath);
                        }
                        bestPaths[neighbour] = newBestPaths;
                    }
                    else if (newScore == bestScores[neighbour])
                    {
                        for (std::vector<Vec2> path : bestPaths[current])
                        {
                            std::vector<Vec2> newPath = path;
                            newPath.push_back(neighbour.pos);
                            bestPaths[neighbour].push_back(newPath);
                        }
                    }
                    continue;
                }
                bestScores[neighbour] = newScore;
                std::vector<std::vector<Vec2>> newBestPaths;
                for (std::vector<Vec2> path : bestPaths[current])
                {
                    std::vector<Vec2> newPath = path;
                    newPath.push_back(neighbour.pos);
                    newBestPaths.push_back(newPath);
                }
                bestPaths[neighbour] = newBestPaths;
                frontier.push(neighbour);
            }
        }
    }
    int bestScore = INT_MAX;
    std::vector<Vec2> directions;
    for (int i = -1; i <= 1; i += 2)
    {
        if (bestScores.find({end, {i, 0}}) == bestScores.end())
        {
            continue;
        }
        if (bestScores[{end, {i, 0}}] < bestScore)
        {
            bestScore = bestScores[{end, {i, 0}}];
            directions.push_back({i, 0});
        }
    }
    for (int i = -1; i <= 1; i += 2)
    {
        if (bestScores.find({end, {0, i}}) == bestScores.end())
        {
            continue;
        }
        if (bestScores[{end, {0, i}}] < bestScore)
        {
            bestScore = bestScores[{end, {0, i}}];
            directions.push_back({0, i});
        }
    }
    std::unordered_set<Vec2, Vec2Hash> nodesAlongBestPaths;
    for (Vec2 dir : directions)
    {
        for (std::vector<Vec2> path : bestPaths[{end, dir}])
        {
            for (Vec2 node : path)
            {
                nodesAlongBestPaths.insert(node);
            }
        }
    }
    return nodesAlongBestPaths.size();
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