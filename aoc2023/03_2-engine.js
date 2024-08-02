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

class Element {
  // Constructor method
  constructor(coord, str) {
    this.coord = coord;
    this.str = str;
    this.gear_nums = [];   // gear_nums is supposed to be used only for Stars
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

  adjacentStar(star_index) {
    let coords = this.coordsAround();
    for (let c = 0; c < coords.length; c++) {
      i = coords[c].i;
      j = coords[c].j;
      if (stars[star_index].coord.i === i && stars[star_index].coord.j === j)
        stars[star_index].gear_nums.push(+this.str);
    }
  }
}

function isDigit(c) {
  return ('0' <= c) && (c <= '9');
}

function isStar(c) {
  return c === '*';
}

function validCoord(coord) {
  m = map.length;
  n = map[0].length;
  i = coord.i; j = coord.j;
  return (0 <= i) && (i < m) && (0 <= j) && (j < n);
}

function parseLine(line, i) {
  let j, c, num;
  new_elements = []
  for (j = 0; j < line.length; j++) {
    c = line[j];
    if (isStar(c)) {
      new_elements.push(new Element(new Coord(i, j), '*'));
    }
    else if (!isDigit(c))  // it is '.' or a generic symbol
      continue;
    else {  // it is a number
      num = c;
      let k = 1;
      while (j+k < line.length && isDigit(line[j+k])) {
        num += line[j+k];
        k++
      }
      new_elements.push(new Element(new Coord(i, j), num));
      j += k-1;
    }
  }
  return new_elements
}

let map = [], elements = [], nums = [], stars = [];
let count = 0;
rl.on('line', (line) => {
  new_elements = parseLine(line, count++)
  for (e = 0; e < new_elements.length; e++)
    elements.push(new_elements[e]);
  map.push(line)
});

rl.on('close', () => {
  let sum = 0;
  for (let e = 0; e < elements.length; e++) {   // separating nums and stars
    if (elements[e].str === '*')
      stars.push(elements[e])
    else
      nums.push(elements[e])
  }
  for (let s = 0; s < stars.length; s++) {  // iterating stars
    for (let n = 0; n < nums.length; n++) {
      nums[n].adjacentStar(s);
    }
    if (stars[s].gear_nums.length === 2) {
      sum += stars[s].gear_nums[0] * stars[s].gear_nums[1];
    }
  }
  console.log(sum);
});
