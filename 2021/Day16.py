import math

def main():
    with open("input.txt") as f:
        input = f.read()
        print(f"Part 1 Answer: {part1(input)}")
        print(f"Part 2 Answer: {part2(input)}")

def part1(input):
    packets = [parsePacket(hexToBin(input))[0]]
    versionTotal = 0
    while len(packets) > 0:
        packet = packets.pop()
        versionTotal += packet["version"]
        if packet["type"] != 4:
            packets += packet["data"]
    return versionTotal

def part2(input):
    return evaluatePacket(parsePacket(hexToBin(input))[0])

def parsePacket(binary):
    packet = {"version": binToDen(binary[0:3]), "type": binToDen(binary[3:6])}
    if packet["type"] == 4:
        value = ""
        byte = 0
        while binary[6 + byte * 5] == "1":
            value += binary[6 + byte * 5 + 1 : 6 + (byte + 1) * 5]
            byte += 1
        value += binary[6 + byte * 5 + 1 : 6 + (byte + 1) * 5]
        packet["data"] = binToDen(value)
        return packet, math.ceil((len(binary[: 6 + (byte + 1) * 5]) - 6) / 5) * 5 + 6
    else:
        packet["data"] = []
        if int(binary[6]) == 0:
            length = binToDen(binary[7:22])
            currentLength = 0
            while currentLength < length:
                subPacket, subPacketLength = parsePacket(binary[22 + currentLength:])
                currentLength += subPacketLength
                packet["data"].append(subPacket)
            return packet, 22 + currentLength
        else:
            number = binToDen(binary[7:18])
            currentNumber = 0
            currentLength = 0
            while currentNumber < number:
                subPacket, subPacketLength = parsePacket(binary[18 + currentLength:])
                currentLength += subPacketLength
                currentNumber += 1
                packet["data"].append(subPacket)
            return packet, 18 + currentLength

def evaluatePacket(packet):
    if packet["type"] == 0:
        return sum([evaluatePacket(subpacket) for subpacket in packet["data"]])
    elif packet["type"] == 1:
        return math.prod([evaluatePacket(subpacket) for subpacket in packet["data"]])
    elif packet["type"] == 2:
        return min([evaluatePacket(subpacket) for subpacket in packet["data"]])
    elif packet["type"] == 3:
        return max([evaluatePacket(subpacket) for subpacket in packet["data"]])
    elif packet["type"] == 4:
        return packet["data"]
    elif packet["type"] == 5:
        return int(evaluatePacket(packet["data"][0]) > evaluatePacket(packet["data"][1]))
    elif packet["type"] == 6:
        return int(evaluatePacket(packet["data"][0]) < evaluatePacket(packet["data"][1]))
    elif packet["type"] == 7:
        return int(evaluatePacket(packet["data"][0]) == evaluatePacket(packet["data"][1]))

def hexToBin(hex):
    hexLetters = {"A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15}
    binary = ""
    for char in hex:
        if char in hexLetters:
            value = hexLetters[char]
        else:
            value = int(char)
        for i in range(3, -1, -1):
            if value >= 2 ** i:
                value -= 2 ** i
                binary += "1"
            else:
                binary += "0"
    return binary

def binToDen(bin):
    denary = 0
    for b in range(len(bin)):
        denary += int(bin[b]) * (2 ** (len(bin) - b - 1))
    return denary

if __name__ == '__main__':
    main()