def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    speedRange = 150
    maxSteps = 500
    words = input.split(" ")
    minX = int(words[2].split("..")[0][2:])
    maxX = int(words[2].split("..")[1][:-1])
    minY = int(words[3].split("..")[0][2:])
    maxY = int(words[3].split("..")[1])
    greatestHeight = 0
    for i in range(-speedRange, speedRange + 1):
        for j in range(-speedRange, speedRange + 1):
            x = y = 0
            velX = i
            velY = j
            peak = 0
            steps = 0
            while steps < maxSteps and not(minX <= x <= maxX and minY <= y <= maxY):
                x += velX
                y += velY
                if velX != 0:
                    velX += -(x // abs(x))
                velY -= 1
                if y > peak:
                    peak = y
                steps += 1
            if minX <= x <= maxX and minY <= y <= maxY:
                if peak > greatestHeight:
                    greatestHeight = peak
    return greatestHeight

def part2(input):
    speedRange = 200
    maxSteps = 500
    words = input.split(" ")
    minX = int(words[2].split("..")[0][2:])
    maxX = int(words[2].split("..")[1][:-1])
    minY = int(words[3].split("..")[0][2:])
    maxY = int(words[3].split("..")[1])
    count = 0
    for i in range(-speedRange, speedRange + 1):
        for j in range(-speedRange, speedRange + 1):
            x = y = 0
            velX = i
            velY = j
            steps = 0
            while steps < maxSteps and not(minX <= x <= maxX and minY <= y <= maxY):
                x += velX
                y += velY
                if velX != 0:
                    velX += -(x // abs(x))
                velY -= 1
                steps += 1
            if minX <= x <= maxX and minY <= y <= maxY:
                count += 1
    return count

if __name__ == '__main__':
    main()