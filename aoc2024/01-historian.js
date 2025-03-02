#!/usr/bin/env node

const fs = require("fs");
const path = require("path");

// Parse command-line arguments
const args = process.argv.slice(2); // Skip node and script path
let inputFile = null;
let isPartTwo = false;  // Check if the --two flag is provided

// Parsing arguments
args.forEach(arg => {
  if (arg === "--two") {
    isPartTwo = true; // Set flag if --two is found
  } else if (!inputFile) {
    inputFile = arg; // Treat the first non-flag argument as the input file
  } else {
    console.error(`Unexpected argument: ${arg}`);
    process.exit(1);
  }
});

// Check if the input file was provided
if (!inputFile) {
  console.error(`Usage: ./${path.basename(process.argv[1])} <inputfile> [--two]`);
  process.exit(1);
}

let input = fs.readFileSync(inputFile, "utf8").trim();

let list1 = [];
let list2 = [];

input.split('\n').forEach(line => {
  let [a, b] = line.split(/\s+/).map(x => Number(x));
  list1.push(a);
  list2.push(b);
});

list1.sort((x, y) => x - y);
list2.sort((x, y) => x - y);

function partOne() {
  let sum = 0;

  list1.forEach((val, i) => {
    sum += Math.abs(val - list2[i]);
  });

  console.log(sum);
}

function partTwo() {
  let index = 0;
  let score = 0;
  let lastScore = 0;

  list1.forEach((val, j) => {
    if (j !== 0 && val === list1[j - 1]) {
      score += lastScore;
    }
    else {
      while (index < list2.length && list2[index] < val) {
        index++;
      }
      let appears = 0;
      while (index < list2.length && list2[index] === val) {
        appears++;
        index++;
      }
      score += (lastScore = val * appears);
    }
  });

  console.log(score);
}

// Execute partOne by default, or partTwo if --two is passed
if (isPartTwo) {
  partTwo();
}
else {
  partOne();
}
