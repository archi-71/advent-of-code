import math

def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    data = input.split("\n")
    total = data[0]
    for number in data[1:]:
        total = add(total, number)
    return magnitude(total)

def part2(input):
    data = input.split("\n")
    greatest = 0
    for number1 in data:
        for number2 in data:
            if number1 != number2:
                total = magnitude(add(number1, number2))
                if total > greatest:
                    greatest = total
    return greatest

def add(num1, num2):
    result = f"[{num1},{num2}]"
    prev = ""
    while result != prev:
        prev = result
        result = explode(result)
        if result != prev:
            continue
        result = split(result)
    return result

def explode(num):
    brackets = 0
    for i in range(len(num)):
        if num[i] == "[":
            brackets += 1
        elif num[i] == "]":
            brackets -= 1
        if brackets > 4:
            end = i + 1
            while num[end] != "]":
                end += 1
            pair = num[i+1:end].split(",")
            left = int(pair[0])
            right = int(pair[1])
            newNum = f"{num[:i]}0{num[end+1:]}"
            for j in range(i-2,-1,-1):
                if newNum[j].isnumeric():
                    start = j
                    while newNum[start - 1].isnumeric():
                        start -= 1
                    newNum = f"{newNum[:start]}{int(newNum[start:j+1]) + left}{newNum[j+1:]}"
                    break
            for j in range(i+2,len(newNum)):
                if newNum[j].isnumeric():
                    end = j
                    while newNum[end + 1].isnumeric():
                        end += 1
                    newNum = f"{newNum[:j]}{int(newNum[j:end+1]) + right}{newNum[end+1:]}"
                    break
            return newNum
    return num

def split(num):
    for i in range(len(num)-1):
        if num[i].isnumeric() and num[i+1].isnumeric():
            end = i+1
            while num[end + 1].isnumeric():
                end += 1
            number = int(num[i:end+1])
            newNum = f"{num[:i]}[{math.floor(number / 2)},{math.ceil(number / 2)}]{num[end+1:]}"
            return newNum
    return num

def magnitude(num):
    if num.isnumeric():
        return int(num)
    brackets = 0
    for i in range(len(num)):
        if num[i] == "[":
            brackets += 1
        elif num[i] == "]":
            brackets -= 1
        if num[i] == "," and brackets == 1:
            return 3 * magnitude(num[1:i]) + 2 * magnitude(num[i+1:-1])

if __name__ == '__main__':
    main()