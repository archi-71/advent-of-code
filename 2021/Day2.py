def part1(input):
    data = input.split("\n")
    x = y = 0
    for dir in data:
        dirList = dir.split()
        if dirList[0] == "forward":
            x += int(dirList[1])
        elif dirList[0] == "up":
            y -= int(dirList[1])
        elif dirList[0] == "down":
            y += int(dirList[1])
    return x * y

def part2(input):
    data = input.split("\n")
    x = y = aim = 0
    for dir in data:
        dirList = dir.split()
        if dirList[0] == "forward":
            x += int(dirList[1])
            y += aim * int(dirList[1])
        elif dirList[0] == "up":
            aim -= int(dirList[1])
        elif dirList[0] == "down":
            aim += int(dirList[1])
    return x * y

with open("input.txt") as f:
    input = f.read()
    print(f"Part 1 Answer: {part1(input)}")
    print(f"Part 2 Answer: {part2(input)}")