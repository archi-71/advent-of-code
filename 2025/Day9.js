function part1(input) {
    const data = input.split("\n").map(r => r.split(",").map(x => parseInt(x)));
    let maxArea = 0;
    for (let i = 0; i < data.length; i++) {
        for (let j = i + 1; j < data.length; j++) {
            let sideX = Math.abs(data[i][0] - data[j][0]) + 1;
            let sideY = Math.abs(data[i][1] - data[j][1]) + 1;
            maxArea = Math.max(maxArea, sideX * sideY);
        }
    }
    return maxArea
}

function part2(input) {
    const data = input.split("\n").map(r => r.split(",").map(x => parseInt(x)));
    let maxArea = 0;
    for (let i = 0; i < data.length; i++) {
        for (let j = i + 1; j < data.length; j++) {
            let minX = Math.min(data[i][0], data[j][0]);
            let maxX = Math.max(data[i][0], data[j][0]);
            let minY = Math.min(data[i][1], data[j][1]);
            let maxY = Math.max(data[i][1], data[j][1]);
            let area = (maxX - minX + 1) * (maxY - minY + 1);
            if (area <= maxArea) {
                continue;
            }
            if (isRectInsideShape(data, minX, maxX, minY, maxY)) {
                maxArea = area;
            }
        }
    }
    return maxArea
}

function isRectInsideShape(data, minX, maxX, minY, maxY) {
    let inside = true;
    for (let i = 0; i < data.length; i++) {
        let p1 = data[i];
        let p2 = data[(i + 1) % data.length];
        if (p1[0] == p2[0]) {
            if (p1[0] > minX && p1[0] < maxX) {
                let edgeMinY = Math.min(p1[1], p2[1]);
                let edgeMaxY = Math.max(p1[1], p2[1]);
                if (edgeMinY < maxY && edgeMaxY > minY) {
                    inside = false;
                    break;
                }
            }
        } else if (p1[1] == p2[1]) {
            if (p1[1] > minY && p1[1] < maxY) {
                let edgeMinX = Math.min(p1[0], p2[0]);
                let edgeMaxX = Math.max(p1[0], p2[0]);
                if (edgeMinX < maxX && edgeMaxX > minX) {
                    inside = false;
                    break;
                }
            }
        }
    }
    return inside;
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