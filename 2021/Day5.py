def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    data = input.split("\n")
    grid = [[0 for x in range(1000)] for y in range(1000)]
    for line in data:
        start = [int(num) for num in line.split(" ")[0].split(",")]
        end = [int(num) for num in line.split(" ")[2].split(",")]
        if start[1] == end[1]:
            for x in range(min(start[0], end[0]), max(start[0], end[0])+1):
                grid[start[1]][x] += 1
        elif start[0] == end[0]:
            for y in range(min(start[1], end[1]), max(start[1], end[1])+1):
                grid[y][start[0]] += 1

    total = 0
    for row in grid:
        for num in row:
            if num > 1:
                total += 1
    return total

def part2(input):
    data = input.split("\n")
    grid = [[0 for x in range(1000)] for y in range(1000)]
    for line in data:
        start = [int(num) for num in line.split(" ")[0].split(",")]
        end = [int(num) for num in line.split(" ")[2].split(",")]
        length = max(abs(end[0] - start[0]), abs(end[1] - start[1]))
        direction = [0, 0]
        if end[0] - start[0] != 0:
            direction[0] = int((end[0] - start[0]) / abs((end[0] - start[0])))
        if end[1] - start[1] != 0:
            direction[1] = int((end[1] - start[1]) / abs((end[1] - start[1])))
        for i in range(length + 1):
            grid[start[1] + direction[1] * i][start[0] + direction[0] * i] += 1
            
    total = 0
    for row in grid:
        for num in row:
            if num > 1:
                total += 1
    return total

if __name__ == '__main__':
    main()