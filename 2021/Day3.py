def part1(input):
    data = input.split("\n")
    gamma = epsilon = 0
    for i in range(len(data[0])):
        count = [0, 0]
        for j in range(len(data)):
            count[int(data[j][i])] += 1
        if count[1] > count[0]:
            gamma += 2 ** (len(data[0])-i-1)
        else:
            epsilon += 2 ** (len(data[0])-i-1)
    return gamma * epsilon

def part2(input):
    data = input.split("\n")
    o2Nums = [d for d in data]
    co2Nums = [d for d in data]

    bit = 0
    while len(o2Nums) > 1:
        count = [0, 0]
        for i in range(len(o2Nums)):
            count[int(o2Nums[i][bit])] += 1
        if count[1] >= count[0]:
            mostCommon = "1"
        else:
            mostCommon = "0"
        i = 0
        while i < len(o2Nums):
            if o2Nums[i][bit] != mostCommon:
                o2Nums.pop(i)
            else:
                i += 1
        bit += 1
    o2 = sum([int(o2Nums[0][i]) * (2 ** (len(o2Nums[0])-i-1)) for i in range(len(o2Nums[0]))])

    bit = 0
    while len(co2Nums) > 1:
        count = [0, 0]
        for i in range(len(co2Nums)):
            count[int(co2Nums[i][bit])] += 1
        if count[0] <= count[1]:
            leastCommon = "0"
        else:
            leastCommon = "1"
        i = 0
        while i < len(co2Nums):
            if co2Nums[i][bit] != leastCommon:
                co2Nums.pop(i)
            else:
                i += 1
        bit += 1
    co2 = sum([int(co2Nums[0][i]) * (2 ** (len(co2Nums[0])-i-1)) for i in range(len(co2Nums[0]))])

    return o2 * co2


with open("input.txt") as f:
    input = f.read()
    print(f"Part 1 Answer: {part1(input)}")
    print(f"Part 2 Answer: {part2(input)}")