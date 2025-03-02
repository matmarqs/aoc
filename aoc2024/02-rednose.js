#!/usr/bin/env node

// Import the parseArguments function from utils.js
const { parseArguments } = require("./utils");
const { input, isPartTwo } = parseArguments();

function increasingCondition(a, b) {
  if (1 <= b - a && b - a <= 3)
    return 1; // return 1 if increasing condition
  else if (1 <= a - b && a - b <= 3)
    return -1;  // return -1 if decreasing condition
  else
    return 0; // returns 0 if unsafe
}

function analyzeLevels(level) {
  let increasing = increasingCondition(level[0], level[1]);
  if (increasing === 0)
    return 'unsafe';

  for (let i = 0; i < level.length - 1; i++) {
    if (increasing !== increasingCondition(level[i], level[i + 1]))
      return 'unsafe';
  }
  return 'safe';
}

function partOne() {
  let count = 0;
  input.split('\n').forEach(line => {
    let levels = line.split(' ').map(x => Number(x));
    let report = analyzeLevels(levels);
    count += (report === 'safe') ? 1 : 0;
  });

  console.log(count);
}

function partTwo() {
  function safeRemovingLevel(level) {
    for (let j = 0; j < level.length; j++) {
      if ('safe' === analyzeLevels([...level.slice(0, j), ...level.slice(j + 1)])) {
        return 'safe';
      }
    }
    return 'unsafe';
  }

  let count = 0;
  input.split('\n').forEach(line => {
    let levels = line.split(' ').map(x => Number(x));
    const report = safeRemovingLevel(levels);
    count += (report === 'safe') ? 1 : 0;
  });

  console.log(count);
}

// Execute partOne by default, or partTwo if --two is passed
if (isPartTwo) {
  partTwo();
}
else {
  partOne();
}
