const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: fs.createReadStream(process.argv[2]),
});

class Coord {
  constructor(i, j) {
    this.i = i;
    this.j = j;
  }
}

class Number {
  // Constructor method
  constructor(coord, str) {
    this.coord = coord;
    this.str = str;
  }

  coordsAround() {
    let coords = [], i, j, ij;
    for (i = this.coord.i - 1; i <= this.coord.i + 1; i++) {
      if (i == this.coord.i) {
        ij = new Coord(i, this.coord.j-1); if (validCoord(ij)) coords.push(ij);
        ij = new Coord(i, this.coord.j + this.str.length); if (validCoord(ij)) coords.push(ij);
      }
      else {
        for (j = this.coord.j - 1; j <= this.coord.j + this.str.length; j++) {
          ij = new Coord(i, j);
          if (validCoord(ij)) {
            coords.push(ij);
          }
        }
      }
    }
    return coords
  }

  adjacentSymbol() {
    let coords = this.coordsAround();
    for (let c = 0; c < coords.length; c++) {
      i = coords[c].i;
      j = coords[c].j;
      if (isSymbol(map[i][j]))
        return 1;
    }
    return 0;
  }
}

function isDigit(c) {
  return ('0' <= c) && (c <= '9');
}

function isSymbol(c) {
  return c !== '.' && !isDigit(c);
}

function validCoord(coord) {
  m = map.length;
  n = map[0].length;
  i = coord.i; j = coord.j;
  return (0 <= i) && (i < m) && (0 <= j) && (j < n);
}

function parseLine(line, i) {
  let j, c, num;
  new_numbers = []
  for (j = 0; j < line.length; j++) {
    c = line[j];
    if (!isDigit(c))  // it is '.' or a symbol
      continue;
    else {  // it is a number
      num = c;
      let k = 1;
      while (j+k < line.length && isDigit(line[j+k])) {
        num += line[j+k];
        k++
      }
      new_numbers.push(new Number(new Coord(i, j), num));
      j += k-1;
    }
  }
  return new_numbers
}

let map = [], numbers = [];
let count = 0;
rl.on('line', (line) => {
  new_numbers = parseLine(line, count++)
  for (e = 0; e < new_numbers.length; e++)
    numbers.push(new_numbers[e]);
  map.push(line)
});

rl.on('close', () => {
  let sum = 0;
  for (let n = 0; n < numbers.length; n++) {
    if (numbers[n].adjacentSymbol()) {
      sum += +numbers[n].str;
    }
  }
  console.log(sum);
});
