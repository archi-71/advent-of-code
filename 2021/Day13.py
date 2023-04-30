def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    dots = set()
    foldLines = []
    for row in input.split("\n"):
        if len(row) > 0:
            if row[0] == "f":
                fold = row.split(" ")[2].split("=")
                foldLines.append((fold[0], int(fold[1])))
            else:
                point = [int(x) for x in row.split(",")]
                dots.add((point[0], point[1]))
    newDots = set()
    for dot in dots:
        if foldLines[0][0] == "x":
            if dot[0] > foldLines[0][1]:
                newDots.add((2 * foldLines[0][1] - dot[0], dot[1]))
            else:
                newDots.add(dot)
        elif foldLines[0][0] == "y":
            if dot[1] > foldLines[0][1]:
                newDots.add((dot[0], 2 * foldLines[0][1] - dot[1]))
            else:
                newDots.add(dot)
    return len(newDots)

def part2(input):
    dots = set()
    foldLines = []
    for row in input.split("\n"):
        if len(row) > 0:
            if row[0] == "f":
                fold = row.split(" ")[2].split("=")
                foldLines.append((fold[0], int(fold[1])))
            else:
                point = [int(x) for x in row.split(",")]
                dots.add((point[0], point[1]))
    for line in foldLines:
        newDots = set()
        for dot in dots:
            if line[0] == "x":
                if dot[0] > line[1]:
                    newDots.add((2 * line[1] - dot[0], dot[1]))
                else:
                    newDots.add(dot)
            elif line[0] == "y":
                if dot[1] > line[1]:
                    newDots.add((dot[0], 2 * line[1] - dot[1]))
                else:
                    newDots.add(dot)
        dots = set(newDots)
    paper = [["."]]
    for dot in dots:
        if dot[1] >= len(paper):
            for i in range(dot[1] - len(paper) + 1):
                paper.append(["."] * len(paper[0]))
        if dot[0] >= len(paper[0]):
            for i in range(len(paper)):
                for _ in range(dot[0] - len(paper[i]) + 1):
                    paper[i].append(".")
        paper[dot[1]][dot[0]] = "#"
    return "\n" + "\n".join(["".join(row) for row in paper])

if __name__ == '__main__':
    main()