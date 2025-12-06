function part1(input) {
    const data = input.split("\n").map(
        r => r.trim().replace( /\s\s+/g, ' ' ).split(" ")
    );
    let total = 0;
    for (let i = 0; i < data[0].length; i++) {
        let op = data[data.length - 1][i];
        let answer = op === "+" ? 0 : 1;
        for (let j = 0; j < data.length - 1; j++) {
            num = parseInt(data[j][i]);
            answer = op === "+" ? answer + num : answer * num;
        }
        total += answer;
    }
    return total;
}

function part2(input) {
    const data = input.split("\n").map(r => r.split(""));
    let total = 0;
    let op = data[data.length - 1][0];
    let answer = op === "+" ? 0 : 1;
    for (let i = 0; i < data[0].length; i++) {
        let num = 0;
        for (let j = 0; j < data.length - 1; j++) {
            if (data[j][i] !== " ") {
                num = num * 10 + parseInt(data[j][i]);
            }
        }
        if (num === 0) {
            total += answer;
            op = data[data.length - 1][i + 1];
            answer = op === "+" ? 0 : 1;
            continue;
        }
        answer = op === "+" ? answer + num : answer * num;
    }
    total += answer;
    return total;
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