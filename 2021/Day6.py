def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    fish = [int(x) for x in input.split(",")]
    for i in range(80):
        for j in range(len(fish)):
            if fish[j] == 0:
                fish[j] = 6
                fish.append(8)
            else:
                fish[j] -= 1
    return len(fish)

def part2(input):
    fishGroups = [0] * 9
    for fish in input.split(","):
        fishGroups[int(fish)] += 1
    for i in range(256):
        new = fishGroups[0]
        for j in range(len(fishGroups) - 1):
            fishGroups[j] = fishGroups[j + 1]
        fishGroups[len(fishGroups) - 1] = new
        fishGroups[6] += new
    return sum(fishGroups)

if __name__ == '__main__':
    main()