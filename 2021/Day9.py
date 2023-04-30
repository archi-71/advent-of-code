def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    map = []
    for row in input.split("\n"):
        map.append([int(height) for height in list(row)])
    riskLevelSum = 0
    for i in range(len(map)):
        for j in range(len(map[0])):
            if all([map[i][j] < map[point[1]][point[0]] for point in getAdjacent(map, i, j)]):
                riskLevelSum += map[i][j] + 1
    return riskLevelSum

def part2(input):
    map = []
    for row in input.split("\n"):
        map.append([int(height) for height in list(row)])
    lowPoints = []
    for i in range(len(map)):
        for j in range(len(map[0])):
            if all([map[i][j] < map[point[1]][point[0]] for point in getAdjacent(map, i, j)]):
                lowPoints.append((j, i))
    visited = set()
    basins = []
    for start in lowPoints:
        basins.append(0)
        frontier = [start]
        while len(frontier) > 0:
            current = frontier.pop()
            if current in visited:
                continue
            basins[-1] += 1
            visited.add(current)
            for point in getAdjacent(map, current[1], current[0]):
                if map[point[1]][point[0]] < 9:
                    frontier.append(point)
    basins.sort()
    return basins[-1] * basins[-2] * basins[-3]

def getAdjacent(map, i, j):
    adjacent = []
    for k in range(-1, 2, 2):
        if i + k >= 0 and i + k < len(map):
            adjacent.append((j, i + k))
    for k in range(-1, 2, 2):
        if j + k >= 0 and j + k < len(map[0]):
            adjacent.append((j + k, i))
    return adjacent

if __name__ == '__main__':
    main()