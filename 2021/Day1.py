def part1(input):
    data = input.split("\n")
    increases = 0
    for i in range(1, len(data)):
        if int(data[i]) > int(data[i-1]):
            increases += 1
    return increases

def part2(input):
    data = input.split("\n")
    increases = 0
    for i in range(3, len(data)):
        if int(data[i]) > int(data[i-3]):
            increases += 1
    return increases

with open("input.txt") as f:
    input = f.read()
    print(f"Part 1 Answer: {part1(input)}")
    print(f"Part 2 Answer: {part2(input)}")