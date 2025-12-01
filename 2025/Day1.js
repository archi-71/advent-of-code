function part1(input) {
    const data = input.split("\n");
    let pos = 50;
    let zeroes = 0;
    for (let rot of data) {
        let dir = rot[0] == "R" ? 1 : -1;
        let val = parseInt(rot.slice(1));
        pos += dir * val;
        if (pos % 100 === 0) {
            zeroes++;
        }
    }
    return zeroes;
}

function part2(input) {
    const data = input.split("\n");
    let pos = 50;
    let zeroes = 0;
    for (let rot of data) {
        let dir = rot[0] == "R" ? 1 : -1;
        let val = parseInt(rot.slice(1));
        for (let i = 0; i < val; i++) {
            pos += dir;
            if (pos % 100 === 0) {
                zeroes++;
            }
        }
    }
    return zeroes;
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