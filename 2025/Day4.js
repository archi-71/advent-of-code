function part1(input) {
    const data = input.split("\n").map(r => r.split(""));
    return getAccessible(data).length;
}

function part2(input) {
    let data = input.split("\n").map(r => r.split(""));
    let count = 0;
    let prevCount = -1;
    while (count > prevCount) {
        prevCount = count;
        let accessible = getAccessible(data);
        count += accessible.length;
        for (let [x, y] of accessible) {
            data[y][x] = ".";
        }
    }
    return count;
}

function getAccessible(data) {
    let accessible = [];
    for (let y = 0; y < data.length; y++) {
        for (let x = 0; x < data[y].length; x++) {
            if (data[y][x] === ".") continue;
            let adjacent = 0;
            for (let j = -1; j <= 1; j++) {
                for (let i = -1; i <= 1; i++) {
                    if (i === 0 && j === 0) continue;
                    if (y + j >= 0 && y + j < data.length && x + i >= 0 && x + i < data[y].length) {
                        if (data[y + j][x + i] === "@") {
                            adjacent++;
                        }
                    }
                }
            }
            if (adjacent < 4) {
                accessible.push([x, y]);
            }
        }
    }
    return accessible;
}

const fs = require('fs');
const { get } = require('http');
fs.readFile('input.txt', 'utf8', (err, input) => {
    if (err) {
        console.error('Error reading input:', err);
        return;
    }
    console.log(`Part 1 Answer: ${part1(input)}`);
    console.log(`Part 2 Answer: ${part2(input)}`);
});