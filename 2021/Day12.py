def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    caveLinks = {}
    for row in input.split("\n"):
        edge = row.split("-")
        if edge[0] in caveLinks:
            caveLinks[edge[0]].append(edge[1])
        else:
            caveLinks[edge[0]] = [edge[1]]
        if edge[1] in caveLinks:
            caveLinks[edge[1]].append(edge[0])
        else:
            caveLinks[edge[1]] = [edge[0]]
    pathCount = 0
    paths = [["start"]]
    while len(paths) > 0:
        currentPath = paths.pop()
        currentCave = currentPath[-1]
        if currentCave == "end":
            pathCount += 1
        else:
            for nextCave in caveLinks[currentCave]:
                if not(nextCave.islower() and nextCave in currentPath):
                    newPath = list(currentPath)
                    newPath.append(nextCave)
                    paths.append(newPath)
    return pathCount

def part2(input):
    caveLinks = {}
    for row in input.split("\n"):
        edge = row.split("-")
        if edge[0] in caveLinks:
            caveLinks[edge[0]].append(edge[1])
        else:
            caveLinks[edge[0]] = [edge[1]]
        if edge[1] in caveLinks:
            caveLinks[edge[1]].append(edge[0])
        else:
            caveLinks[edge[1]] = [edge[0]]
    pathCount = 0
    paths = [[["start"], False]]
    while len(paths) > 0:
        currentPath = paths.pop()
        currentCave = currentPath[0][-1]
        visitedSmallCaveTwice = currentPath[1]
        if currentCave == "end":
            pathCount += 1
        else:
            for nextCave in caveLinks[currentCave]:
                if not((nextCave in ["start", "end"] or (nextCave.islower() and visitedSmallCaveTwice)) and nextCave in currentPath[0]):
                    if not(visitedSmallCaveTwice) and nextCave.islower() and nextCave in currentPath[0]:
                        newPath = [list(currentPath[0]), True]
                    else:
                        newPath = [list(currentPath[0]), visitedSmallCaveTwice]
                    newPath[0].append(nextCave)
                    paths.append(newPath)
    return pathCount

if __name__ == '__main__':
    main()