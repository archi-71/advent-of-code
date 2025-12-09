function part1(input, K) {
    const data = input.split("\n").map(r => r.split(",").map(x => parseInt(x)));
    const distances = findDistances(data);
    const circuits = new UnionFind(data.length);
    for (let i = 0; i < K; i++) {
        const [_, i1, i2] = distances[i];
        circuits.union(i1, i2);
    }
    const circuitSizes = [];
    for (let i = 0; i < data.length; i++) {
        const root = circuits.find(i);
        if (!circuitSizes[root]) {
            circuitSizes[root] = circuits.size[root];
        }
    }
    circuitSizes.sort((a, b) => b - a);
    return circuitSizes.slice(0, 3).reduce((a, b) => a * b, 1);
}

function part2(input) {
    const data = input.split("\n").map(r => r.split(",").map(x => parseInt(x)));
    const distances = findDistances(data);
    const circuits = new UnionFind(data.length);
    let i = 0;
    while (circuits.size[circuits.find(0)] < data.length) {
        const [_, i1, i2] = distances[i];
        circuits.union(i1, i2);
        i++;
    }
    return data[distances[i - 1][1]][0] * data[distances[i - 1][2]][0];
}

function findDistances(data) {
    const distances = [];
    for (let i = 0; i < data.length; i++) {
        for (let j = i + 1; j < data.length; j++) {
            let p1 = data[i];
            let p2 = data[j];
            let distance = (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2 + (p1[2] - p2[2]) ** 2;
            distances.push([distance, i, j]);
        }
    }
    distances.sort((a, b) => a[0] - b[0]);
    return distances;
}

class UnionFind {
  constructor(n) {
    this.parent = Array.from({ length: n }, (_, index) => index);
    this.size = Array(n).fill(1);
  }

  find(x) {
    if (this.parent[x] !== x) {
      this.parent[x] = this.find(this.parent[x]);
    }
    return this.parent[x];
  }

  union(x, y) {
    const rootX = this.find(x);
    const rootY = this.find(y);
    if (rootX !== rootY) {
      if (this.size[rootX] < this.size[rootY]) {
        this.parent[rootX] = rootY;
        this.size[rootY] += this.size[rootX];
      } else {
        this.parent[rootY] = rootX;
        this.size[rootX] += this.size[rootY];
      }
    }
  }
}

const fs = require('fs');
fs.readFile('input.txt', 'utf8', (err, input) => {
    if (err) {
        console.error('Error reading input:', err);
        return;
    }
    console.log(`Part 1 Answer: ${part1(input, 1000)}`);
    console.log(`Part 2 Answer: ${part2(input)}`);
});