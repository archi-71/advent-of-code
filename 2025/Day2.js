function part1(input) {
    const data = input.split(",");
    let sum = 0;
    for (let range of data) {
        let id = parseInt(range.split("-")[0]);
        let end = parseInt(range.split("-")[1]);
        while (id <= end) {
            if (id.toString().length % 2 === 0 && id.toString().slice(0, id.toString().length / 2).repeat(2) === id.toString()) {
                sum += id;
            }
            id++;
        }
    }
    return sum;
}

function part2(input) {
    const data = input.split(",");
    let sum = 0;
    for (let range of data) {
        let id = parseInt(range.split("-")[0]);
        let end = parseInt(range.split("-")[1]);
        while (id <= end) {
            for (let rep = 2; rep <= id.toString().length; rep++) {
                if (id.toString().length % rep === 0 && id.toString().slice(0, id.toString().length / rep).repeat(rep) === id.toString()) {
                    sum += id;
                    break;
                }
            }
            id++;
        }
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