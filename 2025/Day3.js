function part1(input) {
    return solve(input, 2);
}

function part2(input) {
    return solve(input, 12);
}

function solve(input, n) {
    const data = input.split("\n");
    let sum = 0;
    for (let bank of data) {
        let batteries = bank.split("").map(x => parseInt(x));
        let start = 0;
        let num = 0;
        for (let i = 0; i < n; i++) {
            digit = Math.max(...batteries.slice(start, batteries.length - n + i + 1));
            start = batteries.indexOf(digit, start) + 1;
            num = num * 10 + digit;
        }
        sum += num;
    }
    return sum;
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