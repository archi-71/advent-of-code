function part1(input) {
    const data = input.split("\n\n");
    const ranges = data[0].split("\n").map(r => r.split("-").map(x => parseInt(x)));
    const ids = data[1].split("\n").map(x => parseInt(x));
    let count = 0;
    for (let id of ids) {
        for (let [start, end] of ranges) {
            if (id >= start && id <= end) {
                count++;
                break;
            }
        }
    }
    return count;
}

function part2(input) {
    const data = input.split("\n\n");
    const ranges = data[0].split("\n").map(r => r.split("-").map(x => parseInt(x)));
    let disjointRanges = [];
    for (let [start, end] of ranges) {
        for (let i = disjointRanges.length - 1; i >= 0; i--) {
            let [disjointStart, disjointEnd] = disjointRanges[i];
            if (end >= disjointStart && start <= disjointEnd) {
                start = Math.min(start, disjointStart);
                end = Math.max(end, disjointEnd);
                disjointRanges.splice(i, 1);
            } 
        }
        disjointRanges.push([start, end]);
    }
    return disjointRanges.reduce((sum, [start, end]) => sum + (end - start + 1), 0);
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