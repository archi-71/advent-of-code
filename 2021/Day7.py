def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    crabs = [int(x) for x in input.split(",")]
    crabs.sort()
    median = crabs[len(crabs) // 2]
    total = 0
    for crab in crabs:
        total += abs(crab - median)
    return total

def part2(input):
    crabs = [int(x) for x in input.split(",")]
    mean = sum(crabs) / len(crabs)
    lower, upper = int(mean), int(mean) + 1
    lowerTotal = upperTotal = 0
    for crab in crabs:
        distance = abs(crab - lower)
        lowerTotal += int(0.5 * distance * (distance + 1))
        distance = abs(crab - upper)
        upperTotal += int(0.5 * distance * (distance + 1))
    return min(lowerTotal, upperTotal)

if __name__ == '__main__':
    main()