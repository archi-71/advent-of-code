def part1(input):
    draws, boards = parseInput(input)
    for draw in draws:
        for board in boards:
            board = markBoard(board, draw)
            if checkIfWon(board):
                return getScore(board, draw)
    return None

def part2(input):
    draws, boards = parseInput(input)
    for draw in draws:
        i = 0
        while i < len(boards):
            boards[i] = markBoard(boards[i], draw)
            if checkIfWon(boards[i]):
                if len(boards) == 1:
                    return getScore(boards[i], draw)
                else:
                    boards.pop(i)
            else:
                i += 1
    return None

def parseInput(input):
    data = input.split("\n")
    draws = data[0].split(",")
    boards = []
    for i in range(1, len(data)):
        if data[i] == "":
            boards.append([])
        else:
            boards[-1].append([[num, False] for num in data[i].split()])
    return draws, boards

def markBoard(board, drawn):
    for i in range(len(board)):
        for j in range(len(board[0])):
            if drawn == board[i][j][0]:
                board[i][j][1] = True
    return board

def checkIfWon(board):
    for i in range(len(board)):
        if all([board[i][j][1] for j in range(len(board[0]))]):
            return True
    for i in range(len(board[0])):
        if all([board[j][i][1] for j in range(len(board))]):
            return True
    return False

def getScore(board, drawn):
    total = 0
    for i in range(len(board)):
        for j in range(len(board[0])):
            if not board[i][j][1]:
                total += int(board[i][j][0])
    return total * int(drawn)

with open("input.txt") as f:
    input = f.read()
    print(f"Part 1 Answer: {part1(input)}")
    print(f"Part 2 Answer: {part2(input)}")