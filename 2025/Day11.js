const graph = new Map();
const memo = new Map();

function part1(input) {
    const data = input.split("\n");
    graph.clear();
    for (let line of data) {
        let [from, to] = line.split(": ");
        graph.set(from, to.split(" "));
    }
    memo.clear();
    return countPaths1("you");
}

function countPaths1(node) {
    if (memo.has(node)) {
        return memo.get(node);
    }
    if (node === "out") {
        memo.set(node, 1);
        return 1;
    }
    let totalPaths = 0;
    for (let neighbor of graph.get(node) || []) {
        totalPaths += countPaths1(neighbor);
    }
    memo.set(node, totalPaths);
    return totalPaths;
}

function part2(input) {
    const data = input.split("\n");
    graph.clear();
    for (let line of data) {
        let [from, to] = line.split(": ");
        graph.set(from, to.split(" "));
    }
    memo.clear();
    return countPaths2("svr", false, false);
}

function countPaths2(node, dac, fft) {
    const key = `${node}-${dac}-${fft}`;
    if (memo.has(key)) {
        return memo.get(key);
    }
    if (node === "out" && dac && fft) {
        memo.set(key, 1);
        return 1;
    }
    if (node === "dac") {
        dac = true;
    }
    if (node === "fft") {
        fft = true;
    }
    let totalPaths = 0;
    for (let neighbor of graph.get(node) || []) {
        totalPaths += countPaths2(neighbor, dac, fft);
    }
    memo.set(key, totalPaths);
    return totalPaths;
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