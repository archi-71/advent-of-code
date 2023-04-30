def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    open = ["(", "[", "{", "<"]
    close = [")", "]", "}", ">"]
    scores = {")": 3, "]": 57, "}": 1197, ">": 25137}
    total = 0
    for line in input.split("\n"):
        prevLine = ""
        while line != prevLine:
            prevLine = line
            for i in range(1, len(line)):
                if line[i-1] in open and line[i] in close and open.index(line[i-1]) == close.index(line[i]):
                    line = line[:i-1] + line[i+1:]
                    break
        for char in line:
            if char not in open:
                total += scores[char]
                break
    return total

def part2(input):
    open = ["(", "[", "{", "<"]
    close = [")", "]", "}", ">"]
    scores = []
    for line in input.split("\n"):
        prevLine = ""
        while line != prevLine:
            prevLine = line
            for i in range(1, len(line)):
                if line[i-1] in open and line[i] in close and open.index(line[i-1]) == close.index(line[i]):
                    line = line[:i-1] + line[i+1:]
                    break
        corrupt = False
        for char in line:
            if char not in open:
                corrupt = True
                break
        if corrupt:
            continue
        scores.append(0)
        for char in line[::-1]:
            scores[-1] *= 5
            scores[-1] += open.index(char) + 1
    scores.sort()
    return scores[len(scores) // 2]

if __name__ == '__main__':
    main()