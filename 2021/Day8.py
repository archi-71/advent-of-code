def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    data = input.split("\n")
    count = 0
    for line in data:
        for num in line.split("|")[1].strip().split(" "):
            if len(num) in [2, 3, 4, 7]:
                count += 1
    return count

def part2(input):
    total = 0
    for line in input.split("\n"):
        signals = line.split("|")[0].strip().split(" ")
        outputs = line.split("|")[1].strip().split(" ")
        numbers = [None] * 10
        fiveSegments = []
        sixSegments = []
        for signal in signals:
            if len(signal) == 2:
                numbers[1] = signal
            elif len(signal) == 3:
                numbers[7] = signal
            elif len(signal) == 4:
                numbers[4] = signal
            elif len(signal) == 5:
                fiveSegments.append(signal)
            elif len(signal) == 6:
                sixSegments.append(signal)
            elif len(signal) == 7:
                numbers[8] = signal
        for i in range(len(fiveSegments)):
            if all([any([segment in fiveSegments[j] and i != j for j in range(len(fiveSegments))]) for segment in fiveSegments[i]]):
                numbers[3] = fiveSegments[i]
                fiveSegments.remove(numbers[3])
                break
        for i in range(len(sixSegments)):
            if all([segment in sixSegments[i] for segment in numbers[3]]):
                numbers[9] = sixSegments[i]
                sixSegments.remove(numbers[9])
                break
        for i in range(len(sixSegments)):
            if all([segment in sixSegments[i] for segment in numbers[1]]):
                numbers[0] = sixSegments[i]
                sixSegments.remove(numbers[0])
                numbers[6] = sixSegments[0]
                break
        for i in range(len(fiveSegments)):
            if all([segment in numbers[6] for segment in fiveSegments[i]]):
                numbers[5] = fiveSegments[i]
                fiveSegments.remove(numbers[5])
                numbers[2] = fiveSegments[0]
                break
        for i in range(len(outputs)):
            for j in range(len(numbers)):
                if len(outputs[i]) == len(numbers[j]) and all([segment in outputs[i] for segment in numbers[j]]):
                    total += j * (10 ** (3 - i))
                    break
    return total

if __name__ == '__main__':
    main()