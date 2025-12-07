function part1(input) {
    const data = input.split("\n").map(r => r.split(""));
    let beams = new Array(data[0].length).fill(false);
    beams[data[0].indexOf("S")] = true;
    let splits = 0;
    for (let row of data) {
        for (let i = 0; i < row.length; i++) {
            if (beams[i] && row[i] === "^") {
                beams[i] = false;
                beams[i - 1] = true;
                beams[i + 1] = true;
                splits++;
            }
        }
    }
    return splits;
}

const memo = new Map();

function part2(input) {
    const data = input.split("\n").map(r => r.split(""));
    memo.clear();
    return recurse(data, 0, data[0].indexOf("S"));
}

function recurse(data, row, col) {
    const key = `${row},${col}`;
    if (memo.has(key)) {
        return memo.get(key);
    }
    while (row < data.length) {
        if (data[row][col] === "^") {
            let left = recurse(data, row + 1, col - 1);
            let right = recurse(data, row + 1, col + 1);
            memo.set(key, left + right);
            return left + right;
        }
        row++;
    }
    memo.set(key, 1);
    return 1;
}

const fs = require('fs');
fs.readFile('input.txt', 'utf8', (err, input) => {
    if (err) {
        console.error('Error reading input:', err);
        return;
    }
    console.log(`Part 1 Answer: ${part1(input)}`);
    console.log(`Part 2 Answer: ${part2(input)}`);
});