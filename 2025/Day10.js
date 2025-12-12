function part1(input) {
    const data = input.split("\n").map(r => r.split(" "));
    let sum = 0;
    for (let machine of data) {
        let lights = machine[0].slice(1, machine[0].length - 1);
        let buttons = machine.slice(1, machine.length - 1).map(x => x.slice(1, x.length).split(",").map(y => parseInt(y)));
        let queue = [];
        let visited = new Set();
        queue.push([".".repeat(lights.length), 0]);
        while (queue.length > 0) {
            let [current, steps] = queue.shift();
            if (current == lights) {
                sum += steps;
                break;
            }
            if (visited.has(current)) {
                continue;
            }
            visited.add(current);
            for (let button of buttons) {
                let next = current.split("");
                for (let index of button) {
                    next[index] = next[index] === "." ? "#" : ".";
                }
                queue.push([next.join(""), steps + 1]);
            }
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
});