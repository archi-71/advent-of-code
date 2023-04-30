def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    data = input.split("\n")
    polymer = data[0]
    rules = {d.split(" -> ")[0] : d.split(" -> ")[1] for d in data[2:]}
    for _ in range(10):
        index = 0
        while index < len(polymer)-1:
            pair = polymer[index] + polymer[index + 1]
            if pair in rules:
                polymer = polymer[:index+1] + rules[pair] + polymer[index+1:]
                index += 1
            index += 1
    frequencies = {}
    for char in polymer:
        if char in frequencies:
            frequencies[char] += 1
        else:
            frequencies[char] = 1
    quantities = list(frequencies.values())
    return max(quantities) - min(quantities)

def part2(input):
    data = input.split("\n")
    pairs = {data[0][i] + data[0][i + 1] : data[0].count(data[0][i] + data[0][i + 1]) for i in range(len(data[0])-1)}
    rules = {d.split(" -> ")[0] : d.split(" -> ")[1] for d in data[2:]}
    for _ in range(40):
        elemPairs = list(pairs.keys())
        freqs = list(pairs.values())
        for i in range(len(elemPairs)):
            if elemPairs[i] in rules:
                insertion = rules[elemPairs[i]]
                if elemPairs[i][0] + insertion in pairs:
                    pairs[elemPairs[i][0] + insertion] += freqs[i]
                else:
                    pairs[elemPairs[i][0] + insertion] = freqs[i]
                if insertion + elemPairs[i][1] in pairs:
                    pairs[insertion + elemPairs[i][1]] += freqs[i]
                else:
                    pairs[insertion + elemPairs[i][1]] = freqs[i]
                pairs[elemPairs[i]] -= freqs[i]
    frequencies = {} 
    for pair in pairs:
        if pair[1] in frequencies:
            frequencies[pair[1]] += pairs[pair]
        else:
            frequencies[pair[1]] = pairs[pair]
    quantities = list(frequencies.values())
    return max(quantities) - min(quantities)

if __name__ == '__main__':
    main()