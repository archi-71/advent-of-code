def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    grid = [[int(risk) for risk in row] for row in input.split("\n")]
    paths = [[[(0,0)], 0]]
    visited = set()
    while len(paths) > 0:
        currentPath = paths.pop(0)
        currentPos = currentPath[0][-1]
        if currentPos in visited:
            continue
        if currentPos == (len(grid[0]) - 1, len(grid) - 1):
            return currentPath[1]
        visited.add(currentPos)
        for nextPos in getAdjacent(grid, currentPos):
            newPath = [list(currentPath[0]), currentPath[1] + grid[nextPos[1]][nextPos[0]]]
            newPath[0].append(nextPos)
            paths = insertInOrder(paths, newPath)
    return None

def part2(input):
    grid = [[((int(risk) - 1 + i + j) % 9) + 1 for i in range(5) for risk in row] for j in range(5) for row in input.split("\n")]
    paths = [[[(0,0)], 0]]
    visited = set()
    while len(paths) > 0:
        currentPath = paths.pop(0)
        currentPos = currentPath[0][-1]
        if currentPos in visited:
            continue
        if currentPos == (len(grid[0]) - 1, len(grid) - 1):
            return currentPath[1]
        visited.add(currentPos)
        for nextPos in getAdjacent(grid, currentPos):
            newPath = [list(currentPath[0]), currentPath[1] + grid[nextPos[1]][nextPos[0]]]
            newPath[0].append(nextPos)
            paths = insertInOrder(paths, newPath)
    return None

def getAdjacent(grid, pos):
    adjacent = []
    for i in range(-1, 2, 2):
        if pos[0] + i >= 0 and pos[0] + i < len(grid[0]):
            adjacent.append((pos[0] + i, pos[1]))
    for i in range(-1, 2, 2):
        if pos[1] + i >= 0 and pos[1] + i < len(grid):
            adjacent.append((pos[0], pos[1] + i))
    return adjacent

def insertInOrder(paths, newPath):
    for i in range(len(paths)):
        if newPath[1] < paths[i][1]:
            paths.insert(i, newPath)
            return paths
    paths.append(newPath)
    return paths

if __name__ == '__main__':
    main()