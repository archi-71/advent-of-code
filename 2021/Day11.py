def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    flashes = 0
    grid = []
    for row in input.split("\n"):
        grid.append([int(x) for x in row])
    for s in range(100):
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                grid[i][j] += 1
        flash = checkFlashes(grid)
        while flash:
            flashes += 1
            grid[flash[0]][flash[1]] += 1
            for i in range(-1, 2):
                for j in range(-1, 2):
                    if flash[0] + i >= 0 and flash[0] + i < len(grid) and flash[1] + j >= 0 and flash[1] + j < len(grid[0]):
                        if grid[flash[0] + i][flash[1] + j] < 10:
                            grid[flash[0] + i][flash[1] + j] += 1
            flash = checkFlashes(grid)
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] >= 10:
                    grid[i][j] = 0
    return flashes

def part2(input):
    steps = 0
    grid = []
    for row in input.split("\n"):
        grid.append([int(x) for x in row])
    while any([grid[i][j] != 0 for i in range(len(grid)) for j in range(len(grid[0]))]):
        steps += 1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                grid[i][j] += 1
        flash = checkFlashes(grid)
        while flash:
            grid[flash[0]][flash[1]] += 1
            for i in range(-1, 2):
                for j in range(-1, 2):
                    if flash[0] + i >= 0 and flash[0] + i < len(grid) and flash[1] + j >= 0 and flash[1] + j < len(grid[0]):
                        if grid[flash[0] + i][flash[1] + j] < 10:
                            grid[flash[0] + i][flash[1] + j] += 1
            flash = checkFlashes(grid)
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] >= 10:
                    grid[i][j] = 0
    return steps

def checkFlashes(grid):
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 10:
                return (i, j)
    return False

if __name__ == '__main__':
    main()